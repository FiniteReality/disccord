#ifndef _client_hpp_
#define _client_hpp_

#include <cpprest/ws_client.h>
#include <string>

#include <token_type.hpp>

#include <rest/client.hpp>

namespace disccord
{
    class Client {
        private:
            web::websockets::client::websocket_client websocket;
            disccord::rest::discord_rest_client rest_client;
        public:
            Client();
            virtual ~Client();
    };
}

#endif /* _client_hpp_ */