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
                virtual ~discord_rest_client();
            private:
                disccord::rest::internal::rest_api_client api_client;
        };
    }
}


#endif /* _client_hpp_ */
