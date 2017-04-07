#include <rest/models/create_guild_ban_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_guild_ban_args::create_guild_ban_args(uint8_t _delete_message_days)
                : delete_message_days(_delete_message_days)
            { }

            create_guild_ban_args::~create_guild_ban_args()
            { }

            void create_guild_ban_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["delete_message_days"] = web::json::value(get_delete_message_days());
            }

            uint8_t create_guild_ban_args::get_delete_message_days()
            {
                return delete_message_days;
            }
        }
    }
}
