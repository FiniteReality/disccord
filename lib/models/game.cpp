#include <models/game.hpp>

namespace disccord
{
    namespace models
    {
        game::game()
        : name(""), url(), type()
        { }

        game::~game()
        { }

        void game::decode(web::json::value json)
        {
            name = json.at("name").as_string();

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

            get_field(url, as_string);
            get_field(type, as_integer);

            #undef get_field
        }

        void game::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value::string(name);
            if (url.is_specified())
                info["url"] = web::json::value(url.get_value());
            if (type.is_specified())
                info["type"] = web::json::value(type.get_value());
        }

        #define define_get_method(field_name) \
            decltype(game::field_name) game::get_##field_name() { \
                return field_name; \
            }

        define_get_method(name)
        define_get_method(url)
        define_get_method(type)

        #undef define_get_method
    }
}
