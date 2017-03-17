#include <boost/lexical_cast.hpp>

#include <models/invite_guild.hpp>

namespace disccord
{
    namespace models
    {
        invite_guild::invite_guild()
            : id(0), name(""),splash(),icon()
        { }

        invite_guild::~invite_guild()
        { }

        void invite_guild::decode(web::json::value json)
        {
            entity::decode(json);
            
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
            name = json.at("name").as_string();
            
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

            get_field(splash, as_string);
            get_field(icon, as_string);

            #undef get_field
        }

        void invite_guild::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);
            
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
            if (splash.is_specified())
                info["splash"] = web::json::value(splash.get_value());
            if (icon.is_specified())
                info["icon"] = web::json::value(icon.get_value());
        }
        
        #define define_get_method(field_name) \
            decltype(invite_guild::field_name) invite_guild::get_##field_name() { \
                return field_name; \
            }
            
        define_get_method(name);
        define_get_method(id);
        define_get_method(splash);
        define_get_method(icon);
        
        #undef define_get_method
    }
}
