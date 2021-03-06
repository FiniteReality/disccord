#include <string>

#include <disccord/models/channel.hpp>

namespace disccord
{
    namespace models
    {
        channel::channel()
            : entity(), guild_id(), last_message_id(),
            position(), bitrate(), user_limit(),
            type(), name(), topic(),
            is_private(),  recipient(), permission_overwrites()
        { }

        channel::~channel()
        { }

        void channel::decode(web::json::value json)
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
            #define get_composite_field_vector(var, type) \
                if (json.has_field(#var)) { \
                    auto _fields_array = json.at(#var).as_array(); \
                    std::vector<type> fields_array(_fields_array.size()); \
                    std::transform(_fields_array.begin(), \
                    _fields_array.end(), fields_array.begin(), \
                    [](web::json::value _field){ \
                        type field; \
                        field.decode(_field); \
                        return field; \
                    }); \
                    var = decltype(var)(fields_array); \
                } else { \
                    var = decltype(var)(); \
                }
            #define get_id_field(var) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(std::stoull(field.as_string())); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_id_field(guild_id);
            get_id_field(last_message_id);
            get_field(position, as_integer);
            get_field(user_limit, as_integer);
            get_field(bitrate, as_integer);
            get_field(name, as_string);
            get_field(type, as_integer);
            get_field(topic, as_string);
            get_field(is_private, as_bool);
            get_composite_field(recipient, user);

            get_composite_field_vector(permission_overwrites, overwrite);

            #undef get_field
            #undef get_id_field
            #undef get_composite_field
            #undef get_composite_field_vector
        }

        void channel::encode_to(std::unordered_map<std::string,
                                                   web::json::value> &info)
        {
            entity::encode_to(info);

            if (position.is_specified())
                info["is_private"] = web::json::value(is_private.get_value());
            if (position.is_specified())
                info["position"] = web::json::value(position.get_value());
            if (user_limit.is_specified())
                info["user_limit"] = web::json::value(user_limit.get_value());
            if (bitrate.is_specified())
                info["bitrate"] = web::json::value(bitrate.get_value());
            if (guild_id.is_specified())
                info["guild_id"] =
                    web::json::value(std::to_string(guild_id.get_value()));
            if (name.is_specified())
                info["name"] = web::json::value(name.get_value());
            if (type.is_specified())
                info["type"] = web::json::value(type.get_value());
            if (topic.is_specified())
                info["topic"] = web::json::value(topic.get_value());
            if (recipient.is_specified())
                info["recipient"] = recipient.get_value().encode();
            if (last_message_id.is_specified()) {
                auto str = std::to_string(last_message_id.get_value());
                info["last_message_id"] = web::json::value(str);
            }
            if (permission_overwrites.is_specified())
            {
                auto _permission_overwrites =
                    permission_overwrites.get_value();
                std::vector<web::json::value>
                    field_array(_permission_overwrites.size());
                std::transform(_permission_overwrites.begin(),
                               _permission_overwrites.end(),
                               field_array.begin(),
                               [](overwrite field)
                    {
                        return field.encode();
                    });
                info["permission_overwrites"] =
                    web::json::value::array(field_array);
            }
        }

        #define define_get_method(field_name) \
            decltype(channel::field_name) channel::get_##field_name() { \
                return field_name; \
            }

        define_get_method(guild_id)
        define_get_method(last_message_id)
        define_get_method(position)
        define_get_method(bitrate)
        define_get_method(user_limit)
        define_get_method(name)
        define_get_method(type)
        define_get_method(topic)
        define_get_method(is_private)
        define_get_method(recipient)
        define_get_method(permission_overwrites)

        #undef define_get_method
    }
}
