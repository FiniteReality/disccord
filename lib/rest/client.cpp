#include <rest/client.hpp>

#include <rest.hpp>

namespace disccord
{
    namespace rest
    {
        discord_rest_client::discord_rest_client(const web::uri& base_uri)
            : web::http::client::http_client(base_uri), buckets()
        {
            setup_discord_handler();
        }

        discord_rest_client::discord_rest_client(const web::uri& base_uri,
            const web::http::client::http_client_config& client_config)
                : web::http::client::http_client(base_uri, client_config)
        {
            setup_discord_handler();
        }

        discord_rest_client::~discord_rest_client()
        { }

        disccord::api::bucket_info discord_rest_client::get_bucket(std::string bucket_url)
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

        /*pplx::task<web::http::http_response> discord_rest_client::request(route_info& route,
            const pplx::cancellation_token& token)
        {
            auto bucket = get_bucket(route.bucket_url);
        }*/

        void discord_rest_client::setup_discord_handler()
        {
            // Set user-agent on a request
            this->add_handler([](auto req, auto pipeline){
                req.headers().add("User-Agent", DISCORD_USER_AGENT);
                return pipeline->propagate(req);
            });
        }
    }
}