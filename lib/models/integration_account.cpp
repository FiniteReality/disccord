#include <string>

#include <models/integration_account.hpp>

namespace disccord
{
    namespace models
    {
        integration_account::integration_account()
            : entity(), name("")
        { }

        integration_account::~integration_account()
        { }

        void integration_account::decode(web::json::value json)
        {
            entity::decode(json);

            name = json.at("name").as_string();
        }

        void integration_account::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["name"] = web::json::value(get_name());
        }

        #define define_get_method(field_name) \
            decltype(integration_account::field_name) integration_account::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);

        #undef define_get_method
    }
}
