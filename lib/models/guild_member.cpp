#include <models/guild_member.hpp>

namespace disccord
{
    namespace models
    {
        guild_member::guild_member()
        : user(), nick(), roles(),
        joined_at(""), deaf(false), mute(false)
        { }

        guild_member::~guild_member()
        { }

        void guild_member::decode(web::json::value json)
        {
            joined_at = json.at("joined_at").as_string();
            deaf = json.at("deaf").as_bool();
            mute = json.at("mute").as_bool();
            
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
                
            get_field(nick, as_string);
            get_composite_field(user, models::user);
            get_composite_field_vector(roles, role);
            
            #undef get_field
            #undef get_composite_field
            #undef get_composite_field_vector
        }

        void guild_member::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["joined_at"] = web::json::value(joined_at);
            info["deaf"] = web::json::value(deaf);
            info["mute"] = web::json::value(mute);
            if (nick.is_specified())
                info["nick"] = web::json::value(nick.get_value());
            if (user.is_specified())
                info["user"] = user.get_value().encode();
            
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
            
            #undef encode_composite_vector
        }
        
        #define define_get_method(field_name) \
            decltype(guild_member::field_name) guild_member::get_##field_name() { \
                return field_name; \
            }

        define_get_method(joined_at)
        define_get_method(deaf)
        define_get_method(mute)
        define_get_method(nick)
        define_get_method(user)
        define_get_method(roles)
        
        #undef define_get_method
    }
}
