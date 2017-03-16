#include <boost/lexical_cast.hpp>

#include <models/emoji.hpp>

namespace disccord
{
    namespace models
    {
        emoji::emoji()
            : name(""), id()
        { }

        emoji::~emoji()
        { }

        void emoji::decode(web::json::value json)
        {
            name = json.at("name").as_string();
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

            get_lexical_field(id, uint64_t);
            
            #undef get_lexical_field
        }

        void emoji::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            if (id.is_specified())
                info["id"] = web::json::value(id.get_value());
        }
        
        #define define_get_method(field_name) \
            decltype(emoji::field_name) emoji::get_##field_name() { \
                return field_name; \
            }
            
        define_get_method(name);
        define_get_method(id);
        
        #undef define_get_method
    }
}
