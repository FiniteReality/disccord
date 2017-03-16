#include <boost/lexical_cast.hpp>

#include <models/channel.hpp>

namespace disccord
{
    namespace models
    {
        channel::channel()
            : id(0), guild_id(), last_message_id(),
            position(), bitrate(), user_limit(),
            name(), type(), topic(),
            is_private(false),  recipient()
        { }

        channel::~channel()
        { }

        void channel::decode(web::json::value json)
        {
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
            is_private = json.at("is_private").as_bool();
            
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
            if (json.has_field("last_message_id"))
                last_message_id = boost::lexical_cast<uint64_t>(json.at("last_message_id").as_string());
            else
                last_message_id = util::optional<uint64_t>::no_value();
            
            if (json.has_field("guild_id"))
                guild_id = boost::lexical_cast<uint64_t>(json.at("guild_id").as_string());
            else
                guild_id = util::optional<uint64_t>::no_value();
            
            get_field(position, as_integer);
            get_field(user_limit, as_integer);
            get_field(bitrate, as_integer);
            get_field(name, as_string);
            get_field(type, as_string);
            get_field(topic, as_string);
            
            get_composite_field(recipient, user);
            
            #undef get_field
            #undef get_composite_field
            
        }

        void channel::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value(id);
            info["is_private"] = web::json::value(is_private);
            
            if (position.is_specified())
                info["position"] = web::json::value::number(position);
            if (user_limit.is_specified())
                info["user_limit"] = web::json::value::number(user_limit);
            if (bitrate.is_specified())
                info["bitrate"] = web::json::value::number(bitrate);
            if (guild_id.is_specified())
                info["guild_id"] = web::json::value::number(guild_id);
            if (name.is_specified())
                info["name"] = web::json::value::string(name);
            if (type.is_specified())
                info["type"] = web::json::value::string(type);
            if (topic.is_specified())
                info["topic"] = web::json::value::string(topic);
            if (recipient.is_specified())
                info["recipient"] = recipient.get_value().encode();
            if (last_message_id.is_specified())
                info["last_message_id"] = web::json::value::number(last_message_id);
            
        }
        
        #define define_get_method(field_name) \
            decltype(channel::field_name) channel::get_##field_name() { \
                return field_name; \
            }
            
        define_get_method(id);
        define_get_method(guild_id);
        define_get_method(last_message_id);
        define_get_method(position);
        define_get_method(bitrate);
        define_get_method(user_limit);
        define_get_method(name);
        define_get_method(type);
        define_get_method(topic);
        define_get_method(is_private);
        define_get_method(recipient);
        
        #undef define_get_method
    }
}
