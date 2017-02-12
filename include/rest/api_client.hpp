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
            class rest_api_client
            {
                public:
                    rest_api_client(const web::uri& base_uri, std::string token, disccord::token_type type);
                    rest_api_client(const web::uri& base_uri, std::string token, disccord::token_type type, const web::http::client::http_client_config& client_config);
                    virtual ~rest_api_client();

                    pplx::task<disccord::models::entity<uint64_t>> request(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none());

                private:
                    disccord::api::bucket_info* get_bucket(route_info& route);

                    web::http::client::http_client http_client;
                    std::unordered_map<std::string, disccord::api::bucket_info*> buckets;
                    std::string token;
                    disccord::token_type token_type;
                    void setup_discord_handler();
            };
        }
    }
}

#endif /* _rest_client_hpp_ */