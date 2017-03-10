#include <boost/lexical_cast.hpp>

#include <models/guild.hpp>

namespace disccord
{
    namespace models
    {
        guild::guild()
            : name(""), region(""), icon(), splash(), owner_id(0),
            afk_channel_id(), embed_channel_id(), afk_timeout(0),
            embed_enabled(false), features()
        { }

        guild::~guild()
        { }

        void guild::decode(web::json::value json)
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
            #define get_lexical_field(var, lexical_type) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(boost::lexical_cast<lexical_type>(field.as_string())); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            name = json.at("name").as_string();
            get_field(icon, as_string);
            get_field(splash, as_string);
            owner_id = boost::lexical_cast<uint64_t>(json.at("owner_id").as_string());
            region = json.at("region").as_string();
            get_lexical_field(afk_channel_id, uint64_t);
            afk_timeout = boost::lexical_cast<int32_t>(json.at("afk_timeout").as_string());
            embed_enabled = json.at("embed_enabled").as_bool();
            get_lexical_field(embed_channel_id, uint64_t);

            if (json.has_field("features"))
            {
                auto _features_array = json.at("features").as_array();
                std::vector<std::string> features_array(_features_array.size());
                std::transform(_features_array.begin(), _features_array.end(), features_array.begin(),
                    [](web::json::value _feature){
                        return _feature.as_string();
                    });
                features = features_array;
            }

            #undef get_field
            #undef get_lexical_field
        }

        void guild::encode_to(std::unordered_map<std::string,web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());
            if (get_icon().is_specified())
                info["icon"] = get_icon();
            if (get_splash().is_specified())
                info["splash"] = get_splash();
            info["owner_id"] = web::json::value::string(std::to_string(get_owner_id()));
            info["region"] = web::json::value(get_region());
            if (get_afk_channel_id().is_specified())
                info["afk_channel_id"] = get_afk_channel_id();
            info["afk_timeout"] = web::json::value::string(std::to_string(get_afk_timeout()));
            info["embed_enabled"] = web::json::value(get_embed_enabled());
            if (get_embed_channel_id().is_specified())
                info["embed_channel_id"] = get_embed_channel_id();
            // TODO: see guild.hpp
            {
                auto _features = get_features();
                std::vector<web::json::value> features_array(_features.size());
                std::transform(_features.begin(), _features.end(), features_array.begin(),
                    [](std::string feature){
                        return web::json::value(feature);
                    });
                info["features"] = web::json::value::array(features_array);
            }
            // TODO: see guild.hpp
        }

        #define define_get_method(field_name) \
            decltype(guild::field_name) guild::get_##field_name() { \
                return field_name; \
            }

        define_get_method(name);
        define_get_method(icon);
        define_get_method(splash);
        define_get_method(owner_id);
        define_get_method(region);
        define_get_method(afk_channel_id);
        define_get_method(afk_timeout);
        define_get_method(embed_enabled);
        define_get_method(embed_channel_id);
        // TODO: see guild.hpp
        define_get_method(features);
        // TODO: see guild.hpp

        #undef define_get_method
    }
}
