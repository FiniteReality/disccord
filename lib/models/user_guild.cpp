#include <boost/lexical_cast.hpp>

#include <models/user_guild.hpp>

namespace disccord
{
    namespace models
    {
        user_guild::user_guild()
            : name(""), icon(""), owner(false), id(0), permissions(0)
        { }

        user_guild::~user_guild()
        { }

        void user_guild::decode(web::json::value json)
        {
            entity::decode(json);
            
            name = json.at("name").as_string();
            icon = json.at("icon").as_string();
            owner = json.at("owner").as_bool();
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
            permissions = json.at("permissions").as_integer();
        }

        void user_guild::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);
            
            info["id"] = web::json::value(id);
            info["name"] = web::json::value(name);
            info["icon"] = web::json::value(icon);
            info["owner"] = web::json::value(owner);
            info["permissions"] = web::json::value(std::to_string(permissions));
        }
        
        int64_t user_guild::get_id()
        {
            return id;
        }
        
        std::string user_guild::get_name()
        {
            return name;
        }

        std::string user_guild::get_icon()
        {
            return icon;
        }

        bool user_guild::get_owner()
        {
            return owner;
        }

        int64_t user_guild::get_permissions()
        {
            return permissions;
        }
    }
}
