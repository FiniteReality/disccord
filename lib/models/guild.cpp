#include <boost/lexical_cast.hpp>

#include <models/guild.hpp>

namespace disccord
{
    namespace models
    {
        guild::guild()
            : name(""), region(""), icon(), splash(), owner_id(0),
            afk_channel_id(), embed_channel_id(), afk_timeout(0),
            mfa_level(0), verification_level(0), default_message_notifications(0),
            embed_enabled(false), features(), roles(), 
            emojis(), members(), channels(), presences()
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
            #define get_composite_field_vector(var, type) \
                if (json.has_field(#var)) { \
                    auto _fields_array = json.at(#var).as_array(); \
                    std::vector<type> fields_array(_fields_array.size()); \
                    std::transform(_fields_array.begin(), _fields_array.end(), fields_array.begin(), \
                    [](web::json::value _field){ \
                        type field; \
                        field.decode(_field); \
                        return field; \
                    }); \
                    var = decltype(var)(fields_array); \
                } else { \
                    var = decltype(var)(); \
                }

            name = json.at("name").as_string();
            get_field(icon, as_string);
            get_field(splash, as_string);
            owner_id = boost::lexical_cast<uint64_t>(json.at("owner_id").as_string());
            region = json.at("region").as_string();
            get_lexical_field(afk_channel_id, uint64_t);
            afk_timeout = json.at("afk_timeout").as_integer();
            mfa_level = json.at("mfa_level").as_integer();
            verification_level = json.at("verification_level").as_integer();
            default_message_notifications = json.at("default_message_notifications").as_integer();
            embed_enabled = json.at("embed_enabled").as_bool();
            get_lexical_field(embed_channel_id, uint64_t);
            get_composite_field_vector(roles, role);
            get_composite_field_vector(emojis, emoji);
            get_composite_field_vector(members, guild_member);
            get_composite_field_vector(channels, channel);
            get_composite_field_vector(presences, presence);

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
            #undef get_composite_field_vector
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
            info["afk_timeout"] = web::json::value(get_afk_timeout());
            info["mfa_level"] = web::json::value(mfa_level);
            info["verification_level"] = web::json::value(verification_level);
            info["default_message_notifications"] = web::json::value(default_message_notifications);
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
            
            #define encode_composite_vector(var, type) \
                if (var.is_specified()) { \
                    auto _array = get_##var().get_value(); \
                    std::vector<web::json::value> array(_array.size()); \
                    std::transform(_array.begin(), _array.end(), array.begin(), \
                    [](type _field){ \
                        return _field.encode(); \
                    }); \
                    info[#var] = web::json::value::array(array); \
                }
                
            encode_composite_vector(roles, role);
            encode_composite_vector(emojis, emoji);
            encode_composite_vector(members, guild_member);
            encode_composite_vector(channels, channel);
            encode_composite_vector(presences, presence);   
                
            #undef encode_composite_vector
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
        define_get_method(mfa_level);
        define_get_method(verification_level);
        define_get_method(default_message_notifications);
        define_get_method(embed_enabled);
        define_get_method(embed_channel_id);
        // TODO: see guild.hpp
        define_get_method(features);
        define_get_method(roles);
        define_get_method(emojis);
        define_get_method(members);
        define_get_method(channels);
        define_get_method(presences);

        #undef define_get_method
    }
}
