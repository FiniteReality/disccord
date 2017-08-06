#ifndef _ws_client_hpp_
#define _ws_client_hpp_

#include <string>

#include <cpprest/ws_client.h>

#include <disccord/types.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

namespace disccord
{

    namespace ws
    {
        class discord_ws_client
        {
            public:
                discord_ws_client(const std::string& token, disccord::token_type type);
                virtual ~discord_ws_client();

                pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());

            private:
                disccord::rest::internal::rest_api_client rest_api_client;
                disccord::ws::internal::ws_api_client ws_api_client;

                pplx::cancellation_token_source heartbeat_cancel_token;
                pplx::task<void> heartbeat_task;

                pplx::task<void> handle_frame(const disccord::models::ws::frame* frame);
                pplx::task<void> heartbeat_loop(int wait_millis);
        };
    }
}

#endif /* _ws_client_hpp_ */
