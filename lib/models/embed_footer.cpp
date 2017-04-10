#include <disccord/models/embed_footer.hpp>

namespace disccord
{
    namespace models
    {
        embed_footer::embed_footer()
            : text(""), icon_url(), proxy_icon_url()
        { }

        embed_footer::~embed_footer()
        { }

        void embed_footer::decode(web::json::value json)
        {
            text = json.at("text").as_string();

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

            get_field(icon_url, as_string);
            get_field(proxy_icon_url, as_string);

            #undef get_field
        }

        void embed_footer::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["text"] = web::json::value(get_text());
            if (get_icon_url().is_specified())
                info["icon_url"] = get_icon_url();
            if (get_proxy_icon_url().is_specified())
                info["proxy_icon_url"] = get_proxy_icon_url();
        }

        std::string embed_footer::get_text()
        {
            return text;
        }
        util::optional<std::string> embed_footer::get_icon_url()
        {
            return icon_url;
        }
        util::optional<std::string> embed_footer::get_proxy_icon_url()
        {
            return proxy_icon_url;
        }
    }
}
