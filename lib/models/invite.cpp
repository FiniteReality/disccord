#include <models/invite.hpp>

namespace disccord
{
    namespace models
    {
        invite::invite()
            : code(""),channel(),guild()
        { }

        invite::~invite()
        { }

        void invite::decode(web::json::value json)
        {
            code = json.at("code").as_string();

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

            get_composite_field(guild, invite_guild);
            get_composite_field(channel, invite_channel);
            
            #undef get_composite_field
        }

        void invite::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["code"] = web::json::value(code);
            
            if (guild.is_specified())
                info["guild"] = guild.get_value().encode();
            if (channel.is_specified())
                info["channel"] = channel.get_value().encode();
        }

        #define define_get_method(field_name) \
            decltype(invite::field_name) invite::get_##field_name() { \
                return field_name; \
            }

        define_get_method(code);
        define_get_method(channel);
        define_get_method(guild);

        #undef define_get_method
    }
}
