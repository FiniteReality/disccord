#include <models/embed_provider.hpp>

namespace disccord
{
    namespace models
    {
        embed_provider::embed_provider()
            : name(""), url()
        { }

        embed_provider::~embed_provider()
        { }

        void embed_provider::decode(web::json::value json)
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

            #undef get_field
        }

        void embed_provider::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            if (url.is_specified())
                info["url"] = web::json::value(url.get_value());
        }

        std::string embed_provider::get_name()
        {
            return name;
        }
        util::optional<std::string> embed_provider::get_url()
        {
            return url;
        }
    }
}
