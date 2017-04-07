#include <rest/models/modify_guild_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_args::modify_guild_args(std::string _name)
            : name(_name)
            { }
            
            modify_guild_args::~modify_guild_args()
            { }

            void modify_guild_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["name"] = web::json::value(get_name());
            }

            std::string modify_guild_args::get_name()
            {
                return name;
            }
        }
    }
}
