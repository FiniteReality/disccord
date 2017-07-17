#include <functional>

#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

#include <disccord/ws/opcode.hpp>

namespace disccord
{
    namespace ws
    {
        static const web::uri base_uri(DISCORD_API_BASE_URL);

        discord_ws_client::discord_ws_client(std::string token, disccord::token_type type)
            : rest_api_client(base_uri, token, type), ws_api_client(rest_api_client, token, type),
            heartbeat_cancel_token(), heartbeat_task()
        {
            ws_api_client.set_frame_handler([this](const disccord::ws::models::frame* frame)
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

        void discord_ws_client::event(event::event ev, std::function<void ()> func)
        {
            dispatcher.on(ev, func);
        }

        pplx::task<void> discord_ws_client::handle_frame(const disccord::ws::models::frame* frame)
        {
            switch (frame->get_opcode())
            {
                case opcode::HELLO:
                    //heartbeat_task = pplx::create_task(std::bind)
                    break;
                default:
                    std::cout << "Unhandled opcode " << frame->get_opcode() << std::endl;
            }

            return pplx::create_task([](){});
        }

        pplx::task<void> heartbeat_loop(int wait_millis)
        {
            /* TODO: this*/
            return pplx::create_task([](){});
        }
    }
}
