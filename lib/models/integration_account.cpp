#include <models/integration_account.hpp>

namespace disccord
{
    namespace models
    {
        integration_account::integration_account()
            : id(""), name("")
        { }

        integration_account::~integration_account()
        { }

        void integration_account::decode(web::json::value json)
        {
            id = json.at("id").as_string();
            name = json.at("name").as_string();
        }

        void integration_account::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
        }
        
        #define define_get_method(field_name) \
            decltype(integration_account::field_name) integration_account::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);
        define_get_method(id);
        
        #undef define_get_method
    }
}
