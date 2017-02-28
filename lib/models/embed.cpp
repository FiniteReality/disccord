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
            date(), color(0), footer(),image(),thumbnail(),
            video(),provider(),author(),fields()
        { }

        embed::~embed()
        { }

        void embed::decode(web::json::value json)
        {
            entity::decode(json);

            // will never throw exceptions
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

            get_field(description, as_string);
            get_field(url, as_string);
            get_field(date, as_string);
            
            #undef get_field
        }

        void embed::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["title"] = web::json::value(get_title());
            info["type"] = web::json::value(get_type());
            info["color"] = web::json::value(get_color());
            if (get_description().is_specified())
                info["description"] = get_description();
            if (get_url().is_specified())
                info["url"] = get_url();
            if (get_date().is_specified())
                info["date"] = get_date();
            
            //can refactor these, seems a bit clunky
            if (get_footer().is_specified()){
                web::json::value obj;
                obj["text"] = web::json::value(get_footer().get_value().get_text());
                if (get_footer().get_value().get_icon_url().is_specified())
                    obj["icon_url"] = web::json::value(get_footer().get_value().get_icon_url().get_value());
                if (get_footer().get_value().get_proxy_icon_url().is_specified())
                    obj["proxy_icon_url"] = web::json::value(get_footer().get_value().get_proxy_icon_url().get_value());
                info["footer"] = obj;
            }
            if (get_image().is_specified()){
                web::json::value obj;
                obj["url"] = web::json::value(get_image().get_value().get_url());
                if (get_image().get_value().get_proxy_url().is_specified())
                    obj["proxy_url"] = web::json::value(get_image().get_value().get_proxy_url().get_value());
                if (get_image().get_value().get_height().is_specified())
                    obj["height"] = web::json::value(get_image().get_value().get_height().get_value());
                if (get_image().get_value().get_width().is_specified())
                    obj["width"] = web::json::value(get_image().get_value().get_width().get_value());
                info["image"] = obj;
            }
            if (get_thumbnail().is_specified()){
                web::json::value obj;
                obj["url"] = web::json::value(get_thumbnail().get_value().get_url());
                if (get_thumbnail().get_value().get_proxy_url().is_specified())
                    obj["proxy_url"] = web::json::value(get_thumbnail().get_value().get_proxy_url().get_value());
                if (get_thumbnail().get_value().get_height().is_specified())
                    obj["height"] = web::json::value(get_thumbnail().get_value().get_height().get_value());
                if (get_thumbnail().get_value().get_width().is_specified())
                    obj["width"] = web::json::value(get_thumbnail().get_value().get_width().get_value());
                info["thumbnail"] = obj;
            }
            if (get_video().is_specified()){
                web::json::value obj;
                obj["url"] = web::json::value(get_video().get_value().get_url());
                if (get_video().get_value().get_height().is_specified())
                    obj["height"] = web::json::value(get_video().get_value().get_height().get_value());
                if (get_video().get_value().get_width().is_specified())
                    obj["width"] = web::json::value(get_video().get_value().get_width().get_value());
                info["video"] = obj;
            }
            if (get_provider().is_specified()){
                web::json::value obj;
                obj["name"] = web::json::value(get_provider().get_value().get_name());
                if (get_provider().get_value().get_url().is_specified())
                    obj["url"] = web::json::value(get_provider().get_value().get_url().get_value());
                info["provider"] = obj;
            }
            
            if (get_fields().is_specified()){
                std::vector<web::json::value> field_array;
                for (unsigned int i = 0; i < get_fields().get_value().size(); i++){
                    web::json::value obj;
                    obj["name"] = web::json::value(get_fields().get_value()[i].get_name());
                    obj["value"] = web::json::value(get_fields().get_value()[i].get_value());
                    if (get_fields().get_value()[i].get_inline().is_specified())
                        obj["inline"] = web::json::value(get_fields().get_value()[i].get_inline().get_value());
                    field_array.push_back(obj);
                }
                info["fields"] = web::json::value::array(field_array);
            }
            if (get_author().is_specified()){
                web::json::value obj;
                obj["name"] = web::json::value(get_author().get_value().get_name());
                if (get_author().get_value().get_url().is_specified())
                    obj["url"] = web::json::value(get_author().get_value().get_url().get_value());
                if (get_author().get_value().get_icon_url().is_specified())
                    obj["icon_url"] = web::json::value(get_author().get_value().get_icon_url().get_value());
                if (get_author().get_value().get_proxy_icon_url().is_specified())
                    obj["proxy_icon_url"] = web::json::value(get_author().get_value().get_proxy_icon_url().get_value());
                info["author"] = obj;
            }
        }
        
        void embed::set_footer(web::json::value json)
        {
            get_footer().get_value().decode(json);
        }
        void embed::set_image(web::json::value json)
        {
            get_image().get_value().decode(json);
        }
        void embed::set_thumbnail(web::json::value json)
        {
            get_thumbnail().get_value().decode(json);
        }
        void embed::set_video(web::json::value json)
        {
            get_video().get_value().decode(json);
        }
        void embed::set_provider(web::json::value json)
        {
            get_provider().get_value().decode(json);
        }
        void embed::set_author(web::json::value json)
        {
            get_author().get_value().decode(json);
        }
        void embed::add_field(web::json::value json)
        {
            embed_field _field;
            _field.decode(json);
            get_fields().get_value().push_back(_field);
        }
        
        std::string embed::get_title()
        {
            return title;
        }
        std::string embed::get_type()
        {
            return type;
        }
        util::optional<std::string> embed::get_description()
        {
            return description;
        }
        util::optional<std::string> embed::get_url()
        {
            return url;
        }
        util::optional<std::string> embed::get_date()
        {
            return date;
        }
        int embed::get_color()
        {
            return color;
        }
        util::optional<embed_footer> embed::get_footer()
        {
            return footer;
        }
        util::optional<embed_image> embed::get_image()
        {
            return image;
        }
        util::optional<embed_thumbnail> embed::get_thumbnail()
        {
            return thumbnail;
        }
        util::optional<embed_video> embed::get_video()
        {
            return video;
        }
        util::optional<embed_provider> embed::get_provider()
        {
            return provider;
        }
        util::optional<embed_author> embed::get_author()
        {
            return author;
        }
        util::optional<std::vector<embed_field>> embed::get_fields()
        {
            return fields;
        }
    }
}