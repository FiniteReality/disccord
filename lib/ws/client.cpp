#include <chrono>
#include <functional>

#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

#include <disccord/util/task_sleep.hpp>

#include <disccord/models/ws/hello.hpp>

using namespace std::chrono;

namespace disccord
{
    namespace ws
    {
        static const web::uri base_uri(DISCORD_API_BASE_URL);

        discord_ws_client::discord_ws_client(std::string token,
            disccord::token_type type)
            : rest_api_client(base_uri, token, type),
            ws_api_client(rest_api_client, token, type),
            heartbeat_cancel_token(), heartbeat_task(), seq(0)
        {
            ws_api_client.set_frame_handler([this](
                const disccord::models::ws::frame* frame)
            {
                return this->handle_frame(frame);
            });
        }

        pplx::task<void> discord_ws_client::connect(
            const pplx::cancellation_token& token)
        {
            return ws_api_client.connect(token);
        }

        pplx::task<void> discord_ws_client::handle_frame(
            const disccord::models::ws::frame* frame)
        {
            if (frame->s.is_specified())
            {
                uint32_t cur_seq = seq;
                uint32_t new_seq = frame->s;
                if (new_seq > cur_seq)
                    if (!seq.compare_exchange_weak(cur_seq, new_seq))
                        std::cout << "Failed to increment sequence:" <<
                            "Resuming may give bad data" << std::endl;
            }

            switch (frame->op)
            {
                case opcode::HELLO:
                {
                    auto data = frame->get_data<models::ws::hello>();

                    auto func = std::bind(&discord_ws_client::heartbeat_loop,
                        this, data.heartbeat_interval);
                    heartbeat_task = pplx::create_task(func,
                        pplx::task_options(
                            heartbeat_cancel_token.get_token()));

                    return ws_api_client.send_identify();
                }
                case opcode::HEARTBEAT:
                {
                    return ws_api_client.send_heartbeat(seq);
                }
                case opcode::HEARTBEAT_ACK:
                {
                    int64_t now = duration_cast<milliseconds>(
                        high_resolution_clock::now().time_since_epoch())
                        .count();

                    latency = now - last_heartbeat_time;
                    break;
                }
                default:
                    std::cout << "Unhandled opcode " <<
                        static_cast<uint32_t>(frame->op) << std::endl;
            }

            return pplx::create_task([]{});
        }

        void discord_ws_client::heartbeat_loop(int wait_millis)
        {
            while (!pplx::is_task_cancellation_requested())
            {
                int64_t now = duration_cast<milliseconds>(
                    high_resolution_clock::now().time_since_epoch()).count();

                // TODO: this should probably notify the client rather than
                // throw
                if (now > last_heartbeat_time + wait_millis)
                    throw new std::runtime_error("Missed last heartbeat");

                last_heartbeat_time = now;

                ws_api_client.send_heartbeat(seq).then([&]
                {
                    return pplxtra::task::sleep(wait_millis);
                }).wait();
            }

            pplx::cancel_current_task();
        }
    }
}
