#include <string>

#include <disccord/models/overwrite.hpp>

namespace disccord
{
    namespace models
    {
        overwrite::overwrite()
        : entity(), allow(0), deny(0), type("")
        { }

        overwrite::~overwrite()
        { }

        void overwrite::decode(web::json::value json)
        {
            entity::decode(json);

            allow = json.at("allow").as_integer();
            deny = json.at("deny").as_integer();
            type = json.at("type").as_string();
        }

        void overwrite::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["allow"] = web::json::value(get_allow());
            info["deny"] = web::json::value(get_deny());
            info["type"] = web::json::value(get_type());
        }

        #define define_get_method(field_name) \
            decltype(overwrite::field_name) overwrite::get_##field_name() { \
                return field_name; \
            }

        define_get_method(allow)
        define_get_method(deny)
        define_get_method(type)

        #undef define_get_method
    }
}
