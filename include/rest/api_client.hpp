#ifndef _rest_api_client_hpp_
#define _rest_api_client_hpp_

#include <unordered_map>

#include <cpprest/http_client.h>

#include <rest/route.hpp>
#include <api/bucket_info.hpp>

#include <models/entity.hpp>

#include <token_type.hpp>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            class discord_rest_api_client
            {
                public:
                    discord_rest_api_client(const web::uri& base_uri);
                    discord_rest_api_client(const web::uri& base_uri, const web::http::client::http_client_config& client_config);
                    virtual ~discord_rest_api_client();

                    pplx::task<disccord::models::entity<uint64_t>> request(route_info& route, const pplx::cancellation_token& token = pplx::cancellation_token::none());

                protected:
                    disccord::api::bucket_info get_bucket(std::string bucket_url);

                private:
                    web::http::client::http_client http_client;
                    std::unordered_map<std::string, disccord::api::bucket_info> buckets;
                    std::string token;
                    disccord::token_type token_type;
                    void setup_discord_handler();
            };
        }
    }
}

#endif /* _rest_client_hpp_ */