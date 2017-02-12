#include <rest/api_client.hpp>
#include <models/entity.hpp>
#include <rest.hpp>

#include <type_traits>

namespace disccord
{
    namespace rest
    {
        namespace internal
        {
            rest_api_client::rest_api_client(const web::uri& base_uri, std::string acct_token, disccord::token_type type)
                : http_client(base_uri), buckets(), token(acct_token), token_type(type)
            {
                setup_discord_handler();
            }

            rest_api_client::rest_api_client(const web::uri& base_uri, std::string acct_token, disccord::token_type type,
                const web::http::client::http_client_config& client_config)
                    : http_client(base_uri, client_config), buckets(), token(acct_token), token_type(type)
            {
                setup_discord_handler();
            }

            rest_api_client::~rest_api_client()
            {
                for (const auto& entry : buckets)
                {
                    delete entry.second;
                }

                buckets.clear();
            }

            disccord::api::bucket_info* rest_api_client::get_bucket(route_info& info)
            {
                auto bucket_itr = buckets.find(info.bucket_url);
                if (bucket_itr != buckets.end())
                {
                    return bucket_itr->second;
                }
                else
                {
                    auto bucket = new disccord::api::bucket_info(info.method);
                    buckets.emplace(info.bucket_url, bucket);
                    return bucket;
                }
            }

            void rest_api_client::setup_discord_handler()
            {
                // Set user-agent on a request and add authorization header
                http_client.add_handler([=](auto req, auto pipeline){
                    req.headers().add("User-Agent", DISCORD_USER_AGENT);

                    std::string token_type_s;
                    switch (token_type)
                    {
                        case disccord::token_type::Bearer:
                            token_type_s = "Bearer ";
                            break;
                        case disccord::token_type::Bot:
                            token_type_s = "Bot ";
                            break;
                        case disccord::token_type::User:
                            // user tokens don't have a prefix
                            token_type_s = "";
                            break;
                    }

                    req.headers().add("Authorization", token_type_s + token);
                    return pipeline->propagate(req);
                });
            }
        }
    }
}