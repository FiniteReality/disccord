#ifndef _opcode_hpp_
#define _opcode_hpp_

namespace disccord
{
    namespace ws
    {
        enum class opcode
        {
            DISPATCH, //0
            HEARTBEAT,
            IDENTIFY,
            PRESENCE,
            VOICE_STATE,
            VOICE_PING,
            RESUME,
            RECONNECT,
            REQUEST_MEMBERS,
            INVALIDATE_SESSION,
            HELLO, // 10
            HEARTBEAT_ACK,
            GUILD_SYNC
        };
    }
}

#endif /* _opcode_hpp_ */
