#ifndef _rest_api_client_hpp_
#define _rest_api_client_hpp_

#include <cpprest/http_client.h>

#include <rest/route.hpp>
#include <api/bucket_info.hpp>
#include <models/entity.hpp>
#include <token_type.hpp>

#include <unordered_map>

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

                    // Declared here because of silly C++ requirements
                    template <typename T>
                    pplx::task<T> request(route_info& route, pplx::cancellation_token token = pplx::cancellation_token::none())
                    {
                        auto bucket = get_bucket(route);

                        auto base_url = http_client.base_uri().to_string();
                        
                        return bucket->request(http_client, route.full_url).then([=](web::json::value content){
                            return T::decode(content, false);
                        });
                    }

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