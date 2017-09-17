#ifndef _ws_api_client_hpp_
#define _ws_api_client_hpp_

#include <string>
#include <functional>

#include <cpprest/ws_client.h>

#include <disccord/ws/opcode.hpp>

#include <disccord/types.hpp>
#include <disccord/models/ws/frame.hpp>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            class rest_api_client;
        }
    }
    namespace ws
    {
        namespace internal
        {
            class ws_api_client
            {
                public:
                    ws_api_client(disccord::rest::internal::rest_api_client& api_client, std::string token, disccord::token_type type);
                    ws_api_client(disccord::rest::internal::rest_api_client& api_client, std::string token, disccord::token_type type, const web::websockets::client::websocket_client_config& client_config);
                    virtual ~ws_api_client();

                    pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                    pplx::task<void> send(const disccord::models::ws::frame& frame);
                    pplx::task<void> send(disccord::models::ws::frame&& frame);

                    void set_frame_handler(const std::function<pplx::task<void>(const disccord::models::ws::frame*)>& func);

                    pplx::task<void> send_heartbeat(uint32_t sequence);
                    pplx::task<void> send_identify();

                private:
                    web::websockets::client::websocket_callback_client ws_client;
                    std::string token;
                    disccord::token_type token_type;
                    disccord::rest::internal::rest_api_client& rest_api_client;
                    std::function<pplx::task<void>(const disccord::models::ws::frame*)> message_handler;

                    //pplx::task<void> read_task;
                    pplx::cancellation_token_source cancel_token;

                    //void read_loop();
                    pplx::task<void> handle_message(const web::websockets::client::websocket_incoming_message& message);
            };
        }
    }
}

#endif /* _ws_api_client_hpp_ */
