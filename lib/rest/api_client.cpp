#include <rest/api_client.hpp>

#include <models/entity.hpp>

#include <rest.hpp>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            discord_rest_api_client::discord_rest_api_client(const web::uri& base_uri)
                : http_client(base_uri), buckets()
            {
                setup_discord_handler();
            }

            discord_rest_api_client::discord_rest_api_client(const web::uri& base_uri,
                const web::http::client::http_client_config& client_config)
                    : http_client(base_uri, client_config), buckets()
            {
                setup_discord_handler();
            }

            discord_rest_api_client::~discord_rest_api_client()
            { }

            disccord::api::bucket_info discord_rest_api_client::get_bucket(std::string bucket_url)
            {
                auto bucket_itr = buckets.find(bucket_url);
                if (bucket_itr != buckets.end())
                {
                    return bucket_itr->second;
                }
                else
                {
                    auto bucket = disccord::api::bucket_info(bucket_url);
                    buckets.emplace(bucket_url, bucket);
                    return bucket;
                }
            }

            /*pplx::task<disccord::models::entity<uint64_t>> discord_rest_api_client::request(route_info& route,
                const pplx::cancellation_token& token)
            {
                auto bucket = get_bucket(route.bucket_url);

                return bucket.enter().then([=](){
                    return http_client.request(route.full_url, token).then([=](web::http::http_response response){
                        return response.extract_json().then([](web::json::value json){
                            return disccord::models::entity<uint64_t>(0, false);
                        });
                    });
                });
            }*/

            void discord_rest_api_client::setup_discord_handler()
            {
                // Set user-agent on a request
                http_client.add_handler([=](auto req, auto pipeline){
                    req.headers().add("User-Agent", DISCORD_USER_AGENT);

                    std::string token_type_s;
                    switch (token_type)
                    {
                        case disccord::token_type::Bearer:
                            token_type_s = "Bearer";
                            break;
                        case disccord::token_type::Bot:
                            token_type_s = "Bot";
                            break;
                        case disccord::token_type::User:
                            token_type_s = "User";
                            break;
                    }

                    req.headers().add("Authorization", token_type_s + " " + token);
                    return pipeline->propagate(req);
                });
            }
        }
    }
}