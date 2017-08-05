#ifndef _rest_client_hpp_
#define _rest_client_hpp_

#include <disccord/rest/api_client.hpp>

namespace disccord
{
    namespace rest
    {
        class discord_rest_client
        {
            public:
                discord_rest_client();
                discord_rest_client(const std::string& token); //will default token type to 'Bot'
                discord_rest_client(const std::string& token, disccord::token_type type); 
                virtual ~discord_rest_client();

            private:
                disccord::rest::internal::rest_api_client get_client();

                disccord::rest::internal::rest_api_client api_client;
        };
    }
}

#endif /* _client_hpp_ */
