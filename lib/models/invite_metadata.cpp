#include <models/invite_metadata.hpp>

namespace disccord
{
    namespace models
    {
        invite_metadata::invite_metadata()
            : inviter(), created_at(""), uses(0), max_uses(0),
            max_age(0), temporary(false), revoked(false)
        { }

        invite_metadata::~invite_metadata()
        { }

        void invite_metadata::decode(web::json::value json)
        {
            created_at = json.at("created_at").as_string();
            uses = json.at("uses").as_integer();
            max_uses = json.at("max_uses").as_integer();
            max_age = json.at("max_age").as_integer();
            temporary = json.at("temporary").as_bool();
            revoked = json.at("revoked").as_bool();
            
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
            get_composite_field(inviter, user);
            
            #undef get_composite_field
        }

        void invite_metadata::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["created_at"] = web::json::value(created_at);
            info["uses"] = web::json::value(uses);
            info["max_uses"] = web::json::value(max_uses);
            info["max_age"] = web::json::value(max_age);
            info["temporary"] = web::json::value(temporary);
            info["revoked"] = web::json::value(revoked);
            
            if (inviter.is_specified())
                info["inviter"] = inviter.get_value().encode();
        }
        
        #define define_get_method(field_name) \
            decltype(invite_metadata::field_name) invite_metadata::get_##field_name() { \
                return field_name; \
            }
        define_get_method(created_at);
        define_get_method(uses);
        define_get_method(max_uses);
        define_get_method(max_age);
        define_get_method(temporary);
        define_get_method(revoked);
        define_get_method(inviter);
        
        #undef define_get_method
    }
}

