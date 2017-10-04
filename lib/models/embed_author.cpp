#include <disccord/models/embed_author.hpp>

namespace disccord
{
    namespace models
    {
        embed_author::embed_author()
            : name(""), url(), icon_url(), proxy_icon_url()
        { }

        embed_author::~embed_author()
        { }

        void embed_author::decode(web::json::value json)
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
            get_field(icon_url, as_string);
            get_field(proxy_icon_url, as_string);

            #undef get_field
        }

        void embed_author::encode_to(
            std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(get_name());
            if (get_url().is_specified())
                info["url"] = get_url();
            if (get_icon_url().is_specified())
                info["icon_url"] = get_icon_url();
            if (get_proxy_icon_url().is_specified())
                info["proxy_icon_url"] = get_proxy_icon_url();
        }

        std::string embed_author::get_name()
        {
            return name;
        }
        util::optional<std::string> embed_author::get_url()
        {
            return url;
        }
        util::optional<std::string> embed_author::get_icon_url()
        {
            return icon_url;
        }
        util::optional<std::string> embed_author::get_proxy_icon_url()
        {
            return proxy_icon_url;
        }
    }
}
