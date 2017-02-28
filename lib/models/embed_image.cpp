#include <models/embed_image.hpp>

namespace disccord
{
    namespace models
    {
        embed_image::embed_image()
            : url(""), proxy_url(), height(), width()
        { }

        embed_image::~embed_image()
        { }

        void embed_image::decode(web::json::value json)
        {
            entity::decode(json);

            // will never throw exceptions
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

        void embed_image::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["url"] = web::json::value(get_url());
            if (get_proxy_url().is_specified())
                info["proxy_url"] = web::json::value(get_proxy_url().get_value());
            if (get_height().is_specified())
                info["height"] = web::json::value(get_height().get_value());
			if (get_width().is_specified())
                info["width"] = web::json::value(get_width().get_value());
        }

        std::string embed_image::get_url()
        {
            return url;
        }
        util::optional<std::string> embed_image::get_proxy_url()
        {
            return proxy_url;
        }
        util::optional<int> embed_image::get_height()
        {
            return height;
        }
		util::optional<int> embed_image::get_width()
        {
            return width;
        }
    }
}
