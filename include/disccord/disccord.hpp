#ifndef _disccord_hpp_
#define _disccord_hpp_

#define DISCCORD_VERSION "1.0.0-alpha"
#define DISCCORD_PROJECT_URL "https://github.com/FiniteReality/disccord"

#ifndef DISCORD_REST_API_VERSION
#define DISCORD_REST_API_VERSION "6"
#endif /*DISCORD_REST_API_VERSION*/

#ifndef DISCORD_GATEWAY_API_VERSION
#define DISCORD_GATEWAY_API_VERSION "6"
#endif /*DISCORD_GATEWAY_API_VERSION*/

#ifndef DISCORD_USER_AGENT
#define DISCORD_USER_AGENT ("DiscordBot (disccord-" DISCCORD_VERSION "," DISCCORD_PROJECT_URL ")")
#endif /*DISCORD_USER_AGENT*/

#ifndef DISCORD_API_BASE_URL
#define DISCORD_API_BASE_URL "https://discordapp.com/api/v" DISCORD_REST_API_VERSION
#endif /*DISCORD_API_BASE_URL*/

#endif /* _disccord_hpp_ */
