#include <cpprest/ws_client.h>
#include <string>

#include <tokenType.hpp>

namespace disccord
{
    class Client {
        private:
            web::websockets::client::websocket_client websocket;
        public:
            Client();
            virtual ~Client();
    };
}