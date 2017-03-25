#include <models/embed.hpp>

#include <vector>

#include <models/entity.hpp>
#include <models/embed_author.hpp>
#include <models/embed_field.hpp>
#include <models/embed_footer.hpp>
#include <models/embed_image.hpp>
#include <models/embed_video.hpp>
#include <models/embed_thumbnail.hpp>
#include <models/embed_provider.hpp>

namespace disccord
{
    namespace models
    {
        embed::embed()
            : title(""), type("rich"), description(), url(), //default to rich embed, and default color (should enum)
            timestamp(), color(0), footer(),image(),thumbnail(),
            video(),provider(),author(),fields()
        { }

        embed::~embed()
        { }

        void embed::decode(web::json::value json)
        {
            title = json.at("title").as_string();
            type = json.at("type").as_string();
            color = json.at("color").as_integer();

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
            #define get_composite_field(var, type) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        type val; \
                        val.decode(field); \
                        var = decltype(var)(val); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_field(description, as_string);
            get_field(url, as_string);
            get_field(timestamp, as_string);

            get_composite_field(footer, embed_footer);
            get_composite_field(image, embed_image);
            get_composite_field(thumbnail, embed_thumbnail);
            get_composite_field(video, embed_video);
            get_composite_field(provider, embed_provider);
            get_composite_field(author, embed_author);

            if (json.has_field("fields"))
            {
                auto _fields_array = json.at("fields").as_array();
                std::vector<embed_field> fields_array(_fields_array.size());
                std::transform(_fields_array.begin(), _fields_array.end(), fields_array.begin(),
                    [](web::json::value _field){
                        embed_field field;
                        field.decode(_field);
                        return field;
                    });
                fields = fields_array;
            }

            #undef get_field
            #undef get_composite_field
        }

        void embed::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["title"] = web::json::value(title);
            info["type"] = web::json::value(type);
            info["color"] = web::json::value(color);
            if (description.is_specified())
                info["description"] = web::json::value(description.get_value());
            if (url.is_specified())
                info["url"] = web::json::value(url.get_value());
            if (timestamp.is_specified())
                info["timestamp"] = web::json::value(timestamp.get_value());
            if (footer.is_specified())
                info["footer"] = footer.get_value().encode();
            if (image.is_specified())
                info["image"] = image.get_value().encode();
            if (thumbnail.is_specified())
                info["thumbnail"] = thumbnail.get_value().encode();
            if (video.is_specified())
                info["video"] = video.get_value().encode();
            if (provider.is_specified())
                info["provider"] = provider.get_value().encode();
            if (fields.is_specified())
            {
                auto _fields = fields.get_value();
                std::vector<web::json::value> field_array(_fields.size());
                std::transform(_fields.begin(), _fields.end(), field_array.begin(),
                    [](embed_field field){
                        return field.encode();
                    });
                info["fields"] = web::json::value::array(field_array);
            }
            if (author.is_specified())
                info["author"] = author.get_value().encode();
        }

        #define define_get_method(field_name) \
            decltype(embed::field_name) embed::get_##field_name() { \
                return field_name; \
            }

        define_get_method(title);
        define_get_method(type);
        define_get_method(description);
        define_get_method(url);
        define_get_method(timestamp);
        define_get_method(color);
        define_get_method(footer);
        define_get_method(image);
        define_get_method(thumbnail);
        define_get_method(video);
        define_get_method(provider);
        define_get_method(author);
        define_get_method(fields);

        #undef define_get_method
    }
}
