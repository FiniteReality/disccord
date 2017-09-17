#ifndef _dispatch_hpp_
#define _dispatch_hpp_

namespace disccord
{
    namespace ws
    {
        enum class dispatch
        {
            READY,
            RESUMED,
            GUILD_CREATE,
            GUILD_UPDATE,
            GUILD_EMOJIS_UPDATE,
            GUILD_INTEGRATIONS_UPDATE,
            GUILD_SYNC,
            GUILD_DELETE,
            GUILD_MEMBER_ADD,
            GUILD_MEMBER_UPDATE,
            GUILD_MEMBER_REMOVE,
            GUILD_MEMBERS_CHUNK,
            GUILD_ROLE_CREATE,
            GUILD_ROLE_UPDATE,
            GUILD_ROLE_DELETE,
            GUILD_BAN_ADD,
            GUILD_BAN_REMOVE,
            CHANNEL_CREATE,
            CHANNEL_UPDATE,
            CHANNEL_DELETE,
            CHANNEL_PINS_ACK,
            CHANNEL_PINS_UPDATE,
            CHANNEL_RECIPIENT_ADD,
            CHANNEL_RECIPIENT_REMOVE,
            MESSAGE_CREATE,
            MESSAGE_UPDATE,
            MESSAGE_DELETE,
            MESSAGE_DELETE_BULK,
            MESSAGE_ACK,
            PRESENCE_UPDATE,
            TYPING_START,
            USER_UPDATE,
            USER_SETTINGS_UPDATE,
            VOICE_STATE_UPDATE,
            VOICE_SERVER_UPDATE,
        };
    }
}

#endif /* _dispatch_hpp_ */
