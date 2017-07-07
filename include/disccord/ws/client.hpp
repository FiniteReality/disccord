#ifndef _ws_client_hpp_
#define _ws_client_hpp_

#include <string>

#include <cpprest/ws_client.h>

#include <disccord/token_type.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

namespace disccord
{

    namespace ws
    {
        class discord_ws_client
        {
            public:
                discord_ws_client(std::string token, disccord::token_type type);
                virtual ~discord_ws_client();

                pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());

            private:
                disccord::rest::internal::rest_api_client rest_api_client;
                disccord::ws::internal::ws_api_client ws_api_client;
        };
    }
}

#endif /* _ws_client_hpp_ */
