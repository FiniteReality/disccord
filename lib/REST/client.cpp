#include <REST/client.hpp>

#include <REST.hpp>

namespace disccord
{
    namespace REST
    {
        discord_rest_client::discord_rest_client(const web::uri& base_uri)
            : web::http::client::http_client(base_uri)
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