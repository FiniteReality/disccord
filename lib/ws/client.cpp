#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

namespace disccord
{
    namespace ws
    {
        static const web::uri base_uri(DISCORD_API_BASE_URL);

        discord_ws_client::discord_ws_client(std::string token, disccord::token_type type)
            : rest_api_client(base_uri, token, type), ws_api_client(base_uri, rest_api_client, token, type)
        { }

        discord_ws_client::~discord_ws_client()
        { }

        pplx::task<void> discord_ws_client::connect()
        {
            return ws_api_client.connect();
        }
    }
}
