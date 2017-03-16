#include <boost/lexical_cast.hpp>

#include <models/read_state.hpp>

namespace disccord
{
    namespace models
    {
        read_state::read_state()
        : id(0), mention_count(0), last_message_id()
        { }

        read_state::~read_state()
        { }

        void read_state::decode(web::json::value json)
        {
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
            mention_count = json.at("mention_count").as_integer();
            
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
                
            get_lexical_field(last_message_id, uint64_t);
                
            #undef get_lexical_field
        }

        void read_state::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value(id);
            info["mention_count"] = web::json::value(mention_count);
            if (last_message_id.is_specified())
                info["last_message_id"] = web::json::value(last_message_id.get_value());
        }
        
        #define define_get_method(field_name) \
            decltype(read_state::field_name) read_state::get_##field_name() { \
                return field_name; \
            }
        define_get_method(id);
        define_get_method(mention_count);
        define_get_method(last_message_id);
        
        #undef define_get_method
    }
}
