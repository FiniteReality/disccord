#ifndef _types_hpp_
#define _types_hpp_

#include <cstdint>

namespace disccord
{
    using snowflake = uint64_t;
    using discriminator = uint16_t;

    enum class channel_type
    {
        GUILD_TEXT,
        DM,
        GUILD_VOICE,
        GROUP_DM,
        GUILD_CATEGORY
    };

    enum class token_type
    {
        USER,
        BOT,
        BEARER
    };

    // TODO: verify the order of this
    enum class verification_level
    {
        NONE,
        LOW,
        MEDIUM,
        HIGH,
        HIGHER
    };
    // TODO: verify the order of this
    enum class notification_level
    {
        ALL,
        MENTIONS
    };
    // TODO: figure out waht goes here
    enum class mfa_level
    {
        UNKNOWN
    };
}

#endif /* _types_hpp_ */
