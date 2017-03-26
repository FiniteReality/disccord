#include <string>

#include <models/emoji.hpp>

namespace disccord
{
    namespace models
    {
        emoji::emoji()
            : name(""), id()
        { }

        emoji::~emoji()
        { }

        void emoji::decode(web::json::value json)
        {
            name = json.at("name").as_string();

            if (json.has_field("id"))
            {
                id = std::stoull(json.at("id").as_string());
            }
        }

        void emoji::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);

            if (get_id().has_value())
                info["id"] = web::json::value(std::to_string(get_id().get_value()));
        }

        #define define_get_method(field_name) \
            decltype(emoji::field_name) emoji::get_##field_name() { \
                return field_name; \
            }

        define_get_method(name);
        define_get_method(id);

        #undef define_get_method
    }
}
