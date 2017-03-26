#include <string>

#include <models/integration.hpp>

namespace disccord
{
    namespace models
    {
        integration::integration()
            : entity(), role_id(0), name(""), type(""), synced_at(""),
            expire_behavior(0), expire_grace_period(0), enabled(false),
            syncing(false), user(), account()
        { }

        integration::~integration()
        { }

        void integration::decode(web::json::value json)
        {
            entity::decode(json);
            
            role_id = std::stoull(json.at("role_id").as_string());
            name = json.at("name").as_string();
            type = json.at("type").as_string();
            synced_at = json.at("synced_at").as_string();
            expire_behavior = json.at("expire_behavior").as_integer();
            expire_grace_period = json.at("expire_grace_period").as_integer();
            enabled = json.at("enabled").as_bool();
            syncing = json.at("syncing").as_bool();
            
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
            get_composite_field(account, integration_account);
            
            #undef get_composite_field
            
        }

        void integration::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());;
            info["role_id"] = web::json::value(std::to_string(get_role_id()));
            info["synced_at"] = web::json::value(get_synced_at());
            info["expire_behavior"] = web::json::value(get_expire_behavior());
            info["expire_grace_period"] = web::json::value(get_expire_grace_period());
            info["enabled"] = web::json::value(get_enabled());
            info["syncing"] = web::json::value(get_syncing());
            info["type"] = web::json::value(get_type());

            if (user.is_specified())
                info["user"] = user.get_value().encode();
            if (account.is_specified())
                info["account"] = account.get_value().encode();
        }
        
        #define define_get_method(field_name) \
            decltype(integration::field_name) integration::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);
        define_get_method(id);
        define_get_method(type);
        define_get_method(role_id);
        define_get_method(synced_at);
        define_get_method(expire_behavior);
        define_get_method(expire_grace_period);
        define_get_method(enabled);
        define_get_method(syncing);
        define_get_method(user);
        define_get_method(account);
        
        #undef define_get_method
    }
}
