#define LIB_EXPORT __attribute__((__visibility__("default")))

#define DISCCORD_PROJECT_URL ("https://github.com/FiniteReality/disccord")
#define DISCCORD_VERSION_STRING ("Disccord 0.1.0-dev")

#define DISCCORD_USER_AGENT \
	("DiscordBot (" DISCCORD_PROJECT_URL ", " DISCCORD_VERSION_STRING ")")

#define DISCCORD_API_VERSION (6)
#define DISCORD_API_URL \
	("https://discordapp.com/api/v" DISCCORD_API_VERSION "/")
#define DISCORD_CDN_URL ("https://discordcdn.com/")
#define DISCORD_INVITE_URL ("https://discord.gg/")

LIB_EXPORT void disccord_init();
LIB_EXPORT void disccord_cleanup();