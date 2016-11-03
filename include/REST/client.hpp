#ifndef _rest_client_hpp_
#define _rest_client_hpp_

#include <cpprest/http_client.h>

namespace disccord
{
    namespace REST
    {
        class discord_rest_client : public web::http::client::http_client
        {
            public:
                discord_rest_client(const web::uri& base_uri);
                discord_rest_client(const web::uri& base_uri, const web::http::client::http_client_config& client_config);
                virtual ~discord_rest_client();

            private:
                void setup_discord_handler();
        };
    }
}

#endif /* _rest_client_hpp_ */