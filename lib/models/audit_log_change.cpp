#include <disccord/models/audit_log_change.hpp>

namespace disccord
{
    namespace models
    {
        audit_log_change::audit_log_change()
            : key("")
        { }

        audit_log_change::~audit_log_change()
        { }

        void audit_log_change::decode(web::json::value json)
        {
            key = json.at("key").as_string();
        }

        void audit_log_change::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["key"] = web::json::value(key);
        }

        #define define_get_method(field_name) \
            decltype(audit_log_change::field_name) audit_log_change::get_##field_name() { \
                return field_name; \
            }

        define_get_method(key)

        #undef define_get_method
    }
}
