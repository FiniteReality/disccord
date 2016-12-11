#ifndef _REST_hpp_
#define _REST_hpp_

#include <string>

#include <disccord.hpp>
#include <REST/client.hpp>

#define DISCORD_API_VERSION "6"
#define DISCORD_USER_AGENT ("DiscordBot (disccord-" DISCCORD_VERSION "," DISCCORD_PROJECT_URL ")")
#define DISCORD_BASE_URL "https://discordapp.com/api/v" DISCORD_API_VERSION

namespace disccord
{
    namespace REST
    {
        pplx::task<std::string> getGateway(discord_rest_client& client, std::string& encoding);
    }
}

#endif /* _REST_hpp_ */