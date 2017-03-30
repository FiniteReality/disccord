#include <string>

#include <models/attachment.hpp>

namespace disccord
{
    namespace models
    {
        attachment::attachment()
            : entity(), filename(""), url(""), proxy_url(),
            height(), width(), size(0)
        { }

        attachment::~attachment()
        { }

        void attachment::decode(web::json::value json)
        {
            entity::decode(json);

            filename = json.at("filename").as_string();
            url = json.at("url").as_string();
            size = json.at("size").as_integer();

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

        void attachment::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["filename"] = web::json::value(filename);
            info["url"] = web::json::value(url);
            info["size"] = web::json::value(size);

            if (proxy_url.is_specified())
                info["proxy_url"] = web::json::value(proxy_url.get_value());
            if (height.is_specified())
                info["height"] = web::json::value(height.get_value());
            if (width.is_specified())
                info["width"] = web::json::value(width.get_value());
        }

        #define define_get_method(field_name) \
            decltype(attachment::field_name) attachment::get_##field_name() { \
                return field_name; \
            }

        define_get_method(filename)
        define_get_method(url)
        define_get_method(size)
        define_get_method(proxy_url)
        define_get_method(height)
        define_get_method(width)

        #undef define_get_method
    }
}

