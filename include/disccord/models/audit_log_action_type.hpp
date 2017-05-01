#ifndef _audit_log_action_type_hpp_
#define _audit_log_action_type_hpp_

namespace disccord
{
namespace models
{
enum class audit_log_action_type
{
    all = 0, //in json resp, discord represents all as null, will need to make a check
    guild_update = 1,
    channel_create = 10,
    channel_update = 11,
    channel_delete = 12,
    channel_overwrite_create = 13,
    channel_overwrite_update = 14,
    channel_overwrite_delete = 15,
    member_kick = 20,
    member_prune = 21,
    member_ban_add = 22,
    member_ban_remove = 23,
    member_update = 24,
    member_role_update = 25,
    role_create = 30,
    role_update = 31,
    role_delete = 32,
    invite_create = 40,
    invite_update = 41,
    invite_delete = 42,
    webhook_create = 50,
    webhook_update = 51,
    webhook_delete = 52,
    emoji_create = 60,
    emoji_update = 61,
    emoji_delete = 62
};
} //namespace models
} //namesapce disccord

#endif /* _audit_log_action_type_hpp_ */
