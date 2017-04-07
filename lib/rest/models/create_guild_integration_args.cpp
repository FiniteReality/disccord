#include <rest/models/create_guild_integration_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_guild_integration_args::create_guild_integration_args(std::string _type, uint64_t _id)
            : type(_type), id(_id)
            { }
            
            create_guild_integration_args::~create_guild_integration_args()
            { }

            void create_guild_integration_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["type"] = web::json::value(get_type());
                info["id"] = web::json::value(get_id());
            }

            std::string create_guild_integration_args::get_type()
            {
                return type;
            }
            
            uint64_t create_guild_integration_args::get_id()
            {
                return id;
            }
        }
    }
}
