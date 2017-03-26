#include <string>

#include <models/emoji.hpp>

namespace disccord
{
    namespace models
    {
        emoji::emoji()
            : entity(), name("")
        { }

        emoji::~emoji()
        { }

        void emoji::decode(web::json::value json)
        {
            entity::decode(json);

            name = json.at("name").as_string();
        }

        void emoji::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(name);
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
