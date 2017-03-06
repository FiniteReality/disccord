#include <models/embed_video.hpp>

namespace disccord
{
    namespace models
    {
        embed_video::embed_video()
            : url(""), height(), width()
        { }

        embed_video::~embed_video()
        { }

        void embed_video::decode(web::json::value json)
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

            get_field(height, as_integer);
            get_field(width, as_integer);

            #undef get_field
        }

        void embed_video::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["url"] = web::json::value(get_url());
            if (get_height().is_specified())
                info["height"] = web::json::value(get_height().get_value());
            if (get_width().is_specified())
                info["width"] = web::json::value(get_width().get_value());
        }

        std::string embed_video::get_url()
        {
            return url;
        }
        util::optional<int> embed_video::get_height()
        {
            return height;
        }
        util::optional<int> embed_video::get_width()
        {
            return width;
        }
    }
}
