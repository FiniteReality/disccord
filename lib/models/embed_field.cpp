#include <models/embed_field.hpp>

namespace disccord
{
    namespace models
    {
        embed_field::embed_field()
            : name(""), value(""), _inline(false) //default inline to false
        { }

        embed_field::~embed_field()
        { }

        void embed_field::decode(web::json::value json)
        {
            entity::decode(json);

            // will never throw exceptions
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

            _inline = json.at("inline").as_bool();
            //get_field(_inline, as_bool); won't work, "_inline" isnt a key
            #undef get_field
        }

        void embed_field::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());
            info["value"] = web::json::value(get_value());
            info["inline"] = web::json::value(get_inline().get_value());
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
