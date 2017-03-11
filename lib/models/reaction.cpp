#include <models/reaction.hpp>

namespace disccord
{
    namespace models
    {
        reaction::reaction()
            : count(0), me(false), emoji_()
        { }

        reaction::~reaction()
        { }

        void reaction::decode(web::json::value json)
        {
            count = json.at("count").as_integer();
            me = json.at("me").as_bool();
            
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
                
            get_composite_field(emoji_, emoji);    
                
            #undef get_composite_field
        }

        void reaction::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["count"] = web::json::value(count);
            info["me"] = web::json::value(me);
            if (emoji_.is_specified())
                info["emoji"] = emoji_.get_value().encode();
        }
        
        #define define_get_method(field_name) \
            decltype(reaction::field_name) reaction::get_##field_name() { \
                return field_name; \
            }
        define_get_method(count);
        define_get_method(me);
        define_get_method(emoji_);
        
        #undef define_get_method
    }
}
