#include <rest.hpp>

namespace disccord
{
    namespace rest
    {
        discord_rest_client::discord_rest_client()
            : api_client(web::uri(DISCORD_BASE_URL))
        { }

        discord_rest_client::~discord_rest_client()
        { }
    }
}