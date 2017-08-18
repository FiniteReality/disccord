#include <functional>

#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

#include <disccord/util/task_sleep.hpp>

#include <disccord/models/ws/hello.hpp>

namespace disccord
{
    namespace ws
    {
        static const web::uri base_uri(DISCORD_API_BASE_URL);

        discord_ws_client::discord_ws_client(const std::string& token, disccord::token_type type)
            : rest_api_client(base_uri, token, type), ws_api_client(rest_api_client, token, type),
            heartbeat_cancel_token(), heartbeat_task(), seq(0)
        {
            ws_api_client.set_frame_handler([this](const disccord::models::ws::frame* frame)
            {
                return this->handle_frame(frame);
            });
        }

        discord_ws_client::~discord_ws_client()
        { }

        pplx::task<void> discord_ws_client::connect(const pplx::cancellation_token& token)
        {
            return ws_api_client.connect(token);
        }

        pplx::task<void> discord_ws_client::handle_frame(const disccord::models::ws::frame* frame)
        {
            if (frame->s.is_specified())
                seq = frame->s.get_value();

            // TODO: log the opcodes
            switch (frame->op)
            {
                case opcode::HELLO:
                {
                    auto data = frame->get_data<models::ws::hello>();

                    auto func = std::bind(&discord_ws_client::heartbeat_loop, this, data.heartbeat_interval);
                    heartbeat_task = pplx::create_task(func, pplx::task_options(heartbeat_cancel_token.get_token()));

                    break;
                }
                case opcode::HEARTBEAT:
                {
                    ws_api_client.send_heartbeat(seq).wait();
                    break;
                }
                case opcode::HEARTBEAT_ACK:
                {
                    // TODO: calculate latency
                    break;
                }
                default:
                    std::cout << "Unhandled opcode " << static_cast<uint32_t>(frame->op) << std::endl;
            }

            return pplx::create_task([](){});
        }

        pplx::task<void> discord_ws_client::heartbeat_loop(int wait_millis)
        {
            return pplx::create_task([wait_millis,this](){
                while(!pplx::is_task_cancellation_requested())
                {
                    // TODO: make sure discord responded to last heartbeat, error/exception checks

                    ws_api_client.send_heartbeat(seq).wait();

                    auto s = static_cast<double>(wait_millis)/1000;
                    util::task_sleep(s).wait();
                }

                pplx::cancel_current_task();
            });
        }
    }
}
