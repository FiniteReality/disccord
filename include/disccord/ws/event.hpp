#ifndef _event_hpp_
#define _event_hpp_

namespace disccord
{
    namespace ws
    {
        enum class event
        {
            UNKNOWN, //0
            READY,
            RESUMED,
            CHANNEL_CREATE,
            CHANNEL_UPDATE,
            CHANNEL_DELETE,
            GUILD_CREATE,
            GUILD_UPDATE,
            GUILD_DELETE,
            GUILD_BAN_ADD,
            GUILD_BAN_REMOVE, //10
            GUILD_EMOJIS_UPDATE,
            GUILD_INTEGRATIONS_UPDATE,
            GUILD_MEMBER_ADD,
            GUILD_MEMBER_REMOVE,
            GUILD_MEMBER_UPDATE,
            GUILD_MEMBERS_CHUNK,
            GUILD_ROLE_CREATE,
            GUILD_ROLE_UPDATE,
            GUILD_ROLE_DELETE,
            MESSAGE_CREATE, //20
            MESSAGE_UPDATE,
            MESSAGE_DELETE,
            MESSAGE_DELETE_BULK,
            PRESCENCE_UPDATE,
            TYPING_START,
            USER_SETTINGSUPDATE,
            USER_UPDATE,
            VOICE_STATE_UPDATE,
            VOICE_SERVER_UPDATE //29
        };
    }
}

#endif /* _event_hpp_ */
