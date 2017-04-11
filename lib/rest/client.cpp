#include <disccord/rest.hpp>

namespace disccord
{
    namespace rest
    {
        discord_rest_client::discord_rest_client()
        : api_client(web::uri(DISCORD_BASE_URL), "", disccord::token_type::Bot)
        { }

        discord_rest_client::discord_rest_client(std::string token)
        : api_client(web::uri(DISCORD_BASE_URL), token, disccord::token_type::Bot)
        { }
        discord_rest_client::discord_rest_client(std::string token, disccord::token_type type)
        : api_client(web::uri(DISCORD_BASE_URL), token, type)
        { }

        discord_rest_client::~discord_rest_client()
        { }
        
        disccord::rest::internal::rest_api_client discord_rest_client::get_client()
        {
            return api_client;
        }
    }
}
