#include <vector>

#include <disccord/models/audit_log_entry.hpp>

namespace disccord
{
    namespace models
    {
        audit_log_entry::audit_log_entry()
            : target_id(), user_id(0), action_type(0), changes()
        { }

        audit_log_entry::~audit_log_entry()
        { }

        void audit_log_entry::decode(web::json::value json)
        {
            user_id = std::stoull(json.at("user_id").as_string());
            action_type = json.at("action_type").as_integer();

            #define get_id_field(var) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(std::stoull(field.as_string())); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_id_field(target_id);

            if (json.has_field("changes"))
            {
                auto _changes_array = json.at("changes").as_array();
                std::vector<audit_log_change> changes_array(_changes_array.size());
                std::transform(_changes_array.begin(), _changes_array.end(), changes_array.begin(), [](web::json::value _change)
                    {
                        audit_log_change change;
                        change.decode(_change);
                        return change;
                    });
                changes = changes_array;
            }

            #undef get_id_field
        }

        void audit_log_entry::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["user_id"] = web::json::value(std::to_string(user_id));
            info["action_type"] = web::json::value(action_type);
            if (target_id.is_specified())
                info["target_id"] = get_target_id();
            if (changes.is_specified())
            {
                auto _changes = get_changes().get_value();
                std::vector<web::json::value> change_array(_changes.size());
                std::transform(_changes.begin(), _changes.end(), change_array.begin(), [](audit_log_change change)
                    {
                        return change.encode();
                    });
                info["changes"] = web::json::value::array(change_array);
            }
        }

        #define define_get_method(field_name) \
            decltype(audit_log_entry::field_name) audit_log_entry::get_##field_name() { \
                return field_name; \
            }

        define_get_method(target_id)
        define_get_method(user_id)
        define_get_method(action_type)
        define_get_method(changes)

        #undef define_get_method
    }
}
