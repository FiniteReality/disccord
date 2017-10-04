#include <string>

#include <disccord/models/role.hpp>

namespace disccord
{
    namespace models
    {
        role::role()
            : entity(), name(""), color(0), permissions(0),
            position(0), managed(false), mentionable(false), hoist(false)
        { }

        role::~role()
        { }

        void role::decode(web::json::value json)
        {
            entity::decode(json);

            name = json.at("name").as_string();
            color = json.at("color").as_integer();
            permissions = json.at("permissions").as_integer();
            position = json.at("position").as_integer();
            managed = json.at("managed").as_bool();
            mentionable = json.at("mentionable").as_bool();
            hoist = json.at("hoist").as_bool();
        }

        void role::encode_to(std::unordered_map<std::string,
                                                web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());
            info["color"] = web::json::value(get_color());
            info["permissions"] = web::json::value(get_permissions());
            info["position"] = web::json::value(get_position());
            info["managed"] = web::json::value(get_managed());
            info["mentionable"] = web::json::value(get_mentionable());
            info["hoist"] = web::json::value(get_hoist());
        }

        #define define_get_method(field_name) \
            decltype(role::field_name) role::get_##field_name() { \
                return field_name; \
            }

        define_get_method(name)
        define_get_method(color)
        define_get_method(permissions)
        define_get_method(position)
        define_get_method(managed)
        define_get_method(mentionable)
        define_get_method(hoist)

        #undef define_get_method
    }
}
