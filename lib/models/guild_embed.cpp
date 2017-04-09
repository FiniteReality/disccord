#include <string>

#include <models/guild_embed.hpp>

namespace disccord
{
    namespace models
    {
        guild_embed::guild_embed()
            : enabled(false), channel_id(0)
        { }

        guild_embed::~guild_embed()
        { }

        void guild_embed::decode(web::json::value json)
        {
            enabled = json.at("enabled").as_bool();
            channel_id = std::stoull(json.at("channel_id").as_string());
        }

        void guild_embed::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["enabled"] = web::json::value(enabled);
            info["channel_id"] = web::json::value(std::to_string(channel_id));
        }

        #define define_get_method(field_name) \
            decltype(guild_embed::field_name) guild_embed::get_##field_name() { \
                return field_name; \
            }

        define_get_method(enabled)
        define_get_method(channel_id)

        #undef define_get_method
    }
}
