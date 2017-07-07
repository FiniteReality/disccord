#include <string>

#include <disccord/models/user_guild.hpp>

namespace disccord
{
    namespace models
    {
        user_guild::user_guild()
            : entity(), name(""), icon(), owner(false), id(0), permissions(0)
        { }

        user_guild::~user_guild()
        { }

        void user_guild::decode(web::json::value json)
        {
            entity::decode(json);

            #define get_field(var, conv) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(field.conv()); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            name = json.at("name").as_string();
            owner = json.at("owner").as_bool();
            permissions = json.at("permissions").as_integer();
            get_field(icon, as_string);

            #undef get_field
        }

        void user_guild::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());
            info["owner"] = web::json::value(get_owner());
            info["permissions"] = web::json::value(std::to_string(get_permissions()));
            if (get_icon().is_specified())
                info["icon"] = get_icon();
        }

        #define define_get_method(field_name) \
            decltype(user_guild::field_name) user_guild::get_##field_name() { \
                return field_name; \
            }

        define_get_method(id)
        define_get_method(name)
        define_get_method(icon)
        define_get_method(owner)
        define_get_method(permissions)

        #undef define_get_method
    }
}
