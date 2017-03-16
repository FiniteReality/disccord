#include <models/ban.hpp>

namespace disccord
{
    namespace models
    {
        ban::ban()
        : reason(""), user()
        { }

        ban::~ban()
        { }

        void ban::decode(web::json::value json)
        {
            reason = json.at("reason").as_string();
            
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
                
            get_composite_field(user, models::user);
                
            #undef get_composite_field
        }

        void ban::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["reason"] = web::json::value(reason);
            if (user.is_specified())
                info["user"] = user.get_value().encode();
        }
        
        #define define_get_method(field_name) \
            decltype(ban::field_name) ban::get_##field_name() { \
                return field_name; \
            }
        define_get_method(reason);
        define_get_method(user);
        
        #undef define_get_method
    }
}
