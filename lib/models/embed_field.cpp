#include <models/embed_field.hpp>

namespace disccord
{
    namespace models
    {
        embed_field::embed_field()
            : name(""), value(""), _inline() //default inline to false
        { }

        embed_field::~embed_field()
        { }

        void embed_field::decode(web::json::value json)
        {
            name = json.at("name").as_string();
            value = json.at("value").as_string();

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

            get_field(_inline, as_bool);

            #undef get_field
        }

        void embed_field::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["value"] = web::json::value(value);
            if (_inline.is_specified())
                info["inline"] = web::json::value(_inline.get_value());
        }

        std::string embed_field::get_name()
        {
            return name;
        }
        std::string embed_field::get_value()
        {
            return value;
        }
        util::optional<bool> embed_field::get_inline()
        {
            return _inline;
        }
    }
}
