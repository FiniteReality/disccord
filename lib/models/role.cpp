#include <models/role.hpp>

namespace disccord
{
    namespace models
    {
        role::role()
            : id(""), name(""), color(0), permissions(0),
            position(0), managed(false), mentionable(false), hoist(false)
        { }

        role::~role()
        { }

        void role::decode(web::json::value json)
        {
            id = json.at("id").as_string();
            name = json.at("name").as_string();
            color = json.at("color").as_integer();
            permissions = json.at("permissions").as_integer();
            position = json.at("position").as_integer();
            managed = json.at("managed").as_bool();
            mentionable = json.at("mentionable").as_bool();
            hoist = json.at("hoist").as_bool();
        }

        void role::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
            info["color"] = web::json::value(color);
            info["permissions"] = web::json::value(permissions);
            info["position"] = web::json::value(position);
            info["managed"] = web::json::value(managed);
            info["mentionable"] = web::json::value(mentionable);
            info["hoist"] = web::json::value(hoist);
        }
        
        #define define_get_method(field_name) \
            decltype(role::field_name) role::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);
        define_get_method(id);
        define_get_method(color);
        define_get_method(permissions);
        define_get_method(position);
        define_get_method(managed);
        define_get_method(mentionable);
        define_get_method(hoist);
        
        #undef define_get_method
    }
}
