#ifndef _permissions_hpp_
#define _permissions_hpp_

namespace disccord
{
    enum class permissions
    {
        NONE                  = 0,
        // General
        CREATE_INSTANT_INVITE = 1 << 0,
        KICK_MEMBERS          = 1 << 1,
        BAN_MEMBERS           = 1 << 2,
        ADMINISTRATOR         = 1 << 3,
        MANAGE_CHANNELS       = 1 << 4,
        MANAGE_SERVER         = 1 << 5,

        CHANGE_NICKNAME       = 1 << 26,
        MANAGE_NICKNAME       = 1 << 27,
        MANAGE_ROLES          = 1 << 28,
        MANAGE_WEBHOOKS       = 1 << 29,
        MANAGE_EMOJIS         = 1 << 30,

        // Text
        ADD_REACTIONS         = 1 << 6,
        READ_MESSAGES         = 1 << 10,
        SEND_MESSAGES         = 1 << 11,
        SEND_TTS_MESSAGES     = 1 << 12,
        MANAGE_MESSAGES       = 1 << 13,
        EMBED_LINKS           = 1 << 14,
        ATTACH_FILES          = 1 << 15,
        READ_MESSAGE_HISTORY  = 1 << 16,
        MENTION_EVERYONE      = 1 << 17,
        USE_EXTERNAL_EMOJIS   = 1 << 18,

        // Voice
        CONNECT              = 1 << 20,
        SPEAK                = 1 << 21,
        MUTE_MEMBERS         = 1 << 22,
        DEAFEN_MEMBERS       = 1 << 23,
        MOVE_MEMBERS         = 1 << 24,
        USE_VAD              = 1 << 25,
    };
}

#endif /* _permissions_hpp_ */
