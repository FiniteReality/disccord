#include <models/invite_channel.hpp>

namespace disccord
{
    namespace models
    {
        invite_channel::invite_channel()
            : id(""), name(""), type("")
        { }

        invite_channel::~invite_channel()
        { }

        void invite_channel::decode(web::json::value json)
        {
            id = json.at("id").as_string();
            name = json.at("name").as_string();
            type = json.at("type").as_string();
        }

        void invite_channel::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
            info["type"] = web::json::value(type);
        }
        
        #define define_get_method(field_name) \
            decltype(invite_channel::field_name) invite_channel::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);
        define_get_method(id);
        define_get_method(type);
        
        #undef define_get_method
    }
}
