#ifndef _ws_api_client_hpp_
#define _ws_api_client_hpp_

#include <string>

#include <cpprest/ws_client.h>

#include <disccord/token_type.hpp>

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
                    ws_api_client(const web::uri& base_uri, disccord::rest::internal::rest_api_client& api_client, std::string token, disccord::token_type type);
                    ws_api_client(const web::uri& base_uri, disccord::rest::internal::rest_api_client& api_client, std::string token, disccord::token_type type, const web::websockets::client::websocket_client_config& client_config);
                    virtual ~ws_api_client();

                    pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());

                private:
                    web::websockets::client::websocket_callback_client ws_client;
                    std::string token;
                    disccord::token_type token_type;
                    disccord::rest::internal::rest_api_client& rest_api_client;

                    void handle_message(const web::websockets::client::websocket_incoming_message& message);
            };
        }
    }
}

#endif /* _ws_api_client_hpp_ */
