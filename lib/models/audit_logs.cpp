#include <vector>

#include <disccord/models/audit_logs.hpp>

namespace disccord
{
    namespace models
    {
        audit_logs::audit_logs()
            : users(), entries()
        { }

        audit_logs::~audit_logs()
        { }

        void audit_logs::decode(web::json::value json)
        {
            /* if (json.has_field("users"))
            {
                auto _users_array = json.at("users").as_array();
                std::vector<user> users_array(_users_array.size());
                std::transform(_users_array.begin(), _users_array.end(), users_array.begin(), [](web::json::value _user)
                    {
                        models::user user;
                        user.decode(_user);
                        return user;
                    });
                users = users_array;
            } */
            if (json.has_field("audit_log_entries"))
            {
                auto _entries_array = json.at("audit_log_entries").as_array();
                std::vector<audit_log_entry> entries_array(_entries_array.size());
                std::transform(_entries_array.begin(), _entries_array.end(), entries_array.begin(), [](web::json::value _entry)
                    {
                        audit_log_entry entry;
                        entry.decode(_entry);
                        return entry;
                    });
                entries = entries_array;
            }
        }

        void audit_logs::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            if (users.is_specified())
            {
                auto _users = get_users().get_value();
                std::vector<web::json::value> users_array(_users.size());
                std::transform(_users.begin(), _users.end(), users_array.begin(), [](models::user user)
                    {
                        return user.encode();
                    });
                info["users"] = web::json::value::array(users_array);
            }
            if (entries.is_specified())
            {
                auto _entries = get_entries().get_value();
                std::vector<web::json::value> entries_array(_entries.size());
                std::transform(_entries.begin(), _entries.end(), entries_array.begin(), [](audit_log_entry entry)
                    {
                        return entry.encode();
                    });
                info["entries"] = web::json::value::array(entries_array);
            }
        }

        #define define_get_method(field_name) \
            decltype(audit_logs::field_name) audit_logs::get_##field_name() { \
                return field_name; \
            }

        define_get_method(users)
        define_get_method(entries)

        #undef define_get_method
    }
}
