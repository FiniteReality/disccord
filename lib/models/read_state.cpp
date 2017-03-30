#include <string>

#include <models/read_state.hpp>

namespace disccord
{
    namespace models
    {
        read_state::read_state()
        : entity(), mention_count(0), last_message_id()
        { }

        read_state::~read_state()
        { }

        void read_state::decode(web::json::value json)
        {
            entity::decode(json);

            mention_count = json.at("mention_count").as_integer();

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

            get_id_field(last_message_id);

            #undef get_id_field
        }

        void read_state::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["mention_count"] = web::json::value(get_mention_count());
            if (get_last_message_id().is_specified())
                info["last_message_id"] = web::json::value(get_last_message_id().get_value());
        }

        #define define_get_method(field_name) \
            decltype(read_state::field_name) read_state::get_##field_name() { \
                return field_name; \
            }

        define_get_method(mention_count)
        define_get_method(last_message_id)

        #undef define_get_method
    }
}
