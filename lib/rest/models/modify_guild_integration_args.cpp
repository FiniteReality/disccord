#include <rest/models/modify_guild_integration_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_integration_args::modify_guild_integration_args(uint32_t _expire_behavior, uint32_t _expire_grace_period, bool _enable_emoticons)
            : expire_behavior(_expire_behavior), expire_grace_period(_expire_grace_period), enable_emoticons(_enable_emoticons)
            { }
            
            modify_guild_integration_args::~modify_guild_integration_args()
            { }

            void modify_guild_integration_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["expire_behavior"] = web::json::value(get_expire_behavior());
                info["expire_grace_period"] = web::json::value(get_expire_grace_period());
                info["enable_emoticons"] = web::json::value(get_enable_emoticons());
            }

            uint32_t modify_guild_integration_args::get_expire_behavior()
            {
                return expire_behavior;
            }
            
            uint32_t modify_guild_integration_args::get_expire_grace_period()
            {
                return expire_grace_period;
            }
            
            bool modify_guild_integration_args::get_enable_emoticons()
            {
                return enable_emoticons;
            }
        }
    }
}
