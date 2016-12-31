#ifndef _rest_client_hpp_
#define _rest_client_hpp_

#include <unordered_map>

#include <cpprest/http_client.h>

#include <rest/route.hpp>
#include <api/bucket_info.hpp>

namespace disccord
{
    namespace rest
    {
        class discord_rest_client : public web::http::client::http_client
        {
            public:
                discord_rest_client(const web::uri& base_uri);
                discord_rest_client(const web::uri& base_uri, const web::http::client::http_client_config& client_config);
                virtual ~discord_rest_client();

                // TODO: request info class
                pplx::task<web::http::http_response> request(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none());

            protected:
                disccord::api::bucket_info get_bucket(std::string bucket_url);

            private:
                std::unordered_map<std::string, disccord::api::bucket_info> buckets;
                void setup_discord_handler();
        };
    }
}

#endif /* _rest_client_hpp_ */