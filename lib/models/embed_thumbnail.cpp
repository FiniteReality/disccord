#include <models/embed_thumbnail.hpp>

namespace disccord
{
    namespace models
    {
        embed_thumbnail::embed_thumbnail()
            : url(""), proxy_url(), height(), width()
        { }

        embed_thumbnail::~embed_thumbnail()
        { }

        void embed_thumbnail::decode(web::json::value json)
        {
            url = json.at("url").as_string();

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

            get_field(proxy_url, as_string);
            get_field(height, as_integer);
            get_field(width, as_integer);

            #undef get_field
        }

        void embed_thumbnail::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["url"] = web::json::value(url);
            if (proxy_url.is_specified())
                info["proxy_url"] = web::json::value(proxy_url.get_value());
            if (height.is_specified())
                info["height"] = web::json::value(height.get_value());
            if (width.is_specified())
                info["width"] = web::json::value(width.get_value());
        }

        std::string embed_thumbnail::get_url()
        {
            return url;
        }
        util::optional<std::string> embed_thumbnail::get_proxy_url()
        {
            return proxy_url;
        }
        util::optional<int> embed_thumbnail::get_height()
        {
            return height;
        }
        util::optional<int> embed_thumbnail::get_width()
        {
            return width;
        }
    }
}
