#include <disccord/models/voice_state.hpp>

namespace disccord
{
    namespace models
    {
        voice_state::voice_state()
        : guild_id(), channel_id(0), user_id(0),
        session_id(""), deaf(false), mute(false),
        self_deaf(false), self_mute(false), suppress(false)
        { }

        voice_state::~voice_state()
        { }

        void voice_state::decode(web::json::value json)
        {
            channel_id = std::stoull(json.at("channel_id").as_string());
            user_id = std::stoull(json.at("user_id").as_string());
            session_id = json.at("session_id").as_string();
            deaf = json.at("deaf").as_bool();
            mute = json.at("mute").as_bool();
            self_deaf = json.at("self_deaf").as_bool();
            self_mute = json.at("self_mute").as_bool();
            suppress = json.at("suppress").as_bool();

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

            get_field(guild_id, as_integer);

            #undef get_field
        }

        void voice_state::encode_to(
            std::unordered_map<std::string, web::json::value> &info)
        {
            info["channel_id"] = web::json::value(std::to_string(channel_id));
            info["user_id"] = web::json::value(std::to_string(user_id));
            info["session_id"] = web::json::value(session_id);
            info["deaf"] = web::json::value(deaf);
            info["mute"] = web::json::value(mute);
            info["self_deaf"] = web::json::value(self_deaf);
            info["self_mute"] = web::json::value(self_mute);
            info["suppress"] = web::json::value(suppress);
            if (guild_id.is_specified())
                info["guild_id"] = web::json::value(guild_id.get_value());
        }

        #define define_get_method(field_name) \
            decltype(voice_state::field_name) \
                     voice_state::get_##field_name() { \
                return field_name; \
            }

        define_get_method(channel_id)
        define_get_method(user_id)
        define_get_method(guild_id)
        define_get_method(session_id)
        define_get_method(deaf)
        define_get_method(mute)
        define_get_method(self_deaf)
        define_get_method(self_mute)
        define_get_method(suppress)

        #undef define_get_method
    }
}
