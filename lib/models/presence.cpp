#include <boost/lexical_cast.hpp>

#include <models/presence.hpp>

namespace disccord
{
    namespace models
    {
        presence::presence()
        : user(), roles(), game(),
        guild_id(0), status("")
        { }

        presence::~presence()
        { }

        void presence::decode(web::json::value json)
        {
            status = json.at("status").as_string();
            guild_id = boost::lexical_cast<uint64_t>(json.at("guild_id").as_string());
            
            #define get_composite_field(var, type) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        type val; \
                        val.decode(field); \
                        var = decltype(var)(val); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_composite_field(user, models::user);
            get_composite_field(game, models::game);
            
            if (json.has_field("roles"))
            {
                auto _roles_array = json.at("roles").as_array();
                std::vector<uint64_t> roles_array(_roles_array.size());
                std::transform(_roles_array.begin(), _roles_array.end(), roles_array.begin(),
                    [](web::json::value _role){
                        return boost::lexical_cast<uint64_t>(_role.as_string());
                    });
                roles = roles_array;
            }
            
            #undef get_composite_field
        }

        void presence::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["status"] = web::json::value(status);
            info["guild_id"] = web::json::value(guild_id);
            if (user.is_specified())
                info["user"] = user.get_value().encode();
            if (game.is_specified())
                info["game"] = game.get_value().encode();
            {
                auto _roles = roles;
                std::vector<web::json::value> roles_array(_roles.size());
                std::transform(_roles.begin(), _roles.end(), roles_array.begin(),
                    [](uint64_t role){
                        return web::json::value(role);
                    });
                info["roles"] = web::json::value::array(roles_array);
            }
        }
        
        #define define_get_method(field_name) \
            decltype(presence::field_name) presence::get_##field_name() { \
                return field_name; \
            }
        define_get_method(status);
        define_get_method(guild_id);
        define_get_method(user);
        define_get_method(game);
        define_get_method(roles);
        
        #undef define_get_method
    }
}
