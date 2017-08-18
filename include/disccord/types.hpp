#ifndef _types_hpp_
#define _types_hpp_

#include <cstdint>
#include <disccord/permissions.hpp>

namespace disccord
{
    using snowflake = uint64_t;
    using discriminator = uint16_t;
    using color = uint32_t;

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

    enum class mfa_level
    {
        DISABLED,
        ENABLED
    };

    enum class message_type
    {
        DEFAULT,
        RECIPIENT_ADD,
        RECIPIENT_REMOVE,
        CHANNEL_NAME_CHANGE,
        CHANNEL_ICON_CHANGE,
        CHANNEL_PINNED_MESSAGE,
        GUILD_MEMBER_JOIN
    };
}

#endif /* _types_hpp_ */
