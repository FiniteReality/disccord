#include <string>

#include <disccord/models/webhook.hpp>

namespace disccord
{
    namespace models
    {
        webhook::webhook()
            : entity(), guild_id(), channel_id(0),
            user(), name(), avatar(), token("")
        { }

        webhook::~webhook()
        { }

        void webhook::decode(web::json::value json)
        {
            entity::decode(json);

            channel_id = std::stoull(json.at("channel_id").as_string());
            token = json.at("token").as_string();

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

            get_field(name, as_string);
            get_field(avatar, as_string);
            get_id_field(guild_id);

            if (json.has_field("user")) {
                auto field = json.at("user");
                if (!field.is_null()) {
                    models::user val;
                    val.decode(field);
                    user = util::optional<models::user>(val);
                } else {
                    user = util::optional<models::user>::no_value();
                }
            }
            else {
                user = util::optional<models::user>();
            }

            #undef get_field
            #undef get_id_field
        }

        void webhook::encode_to(std::unordered_map<std::string,web::json::value> &info)
        {
            entity::encode_to(info);

            info["channel_id"] = web::json::value(get_channel_id());
            info["token"] = web::json::value(get_token());
            if (get_name().is_specified())
                info["name"] = get_name();
            if (get_avatar().is_specified())
                info["avatar"] = get_avatar();
            if (get_guild_id().is_specified())
                info["guild_id"] = get_guild_id();
            if (user.is_specified())
                info["user"] = user.get_value().encode();
        }

        #define define_get_method(field_name) \
            decltype(webhook::field_name) webhook::get_##field_name() { \
                return field_name; \
            }

        define_get_method(guild_id)
        define_get_method(channel_id)
        define_get_method(user)
        define_get_method(name)
        define_get_method(avatar)
        define_get_method(token)

        #undef define_get_method
    }
}
