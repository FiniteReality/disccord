#ifndef _audit_logs_hpp_
#define _audit_logs_hpp_

#include <disccord/models/model.hpp>
#include <disccord/models/user.hpp>
#include <disccord/models/audit_log_entry.hpp>

namespace disccord
{
    namespace models
    {
        class audit_logs : public model
        {
            public:
                audit_logs();
                virtual ~audit_logs();

                virtual void decode(web::json::value json) override;

                std::vector<user> get_users();
                std::vector<audit_log_entry> get_entries();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::vector<user> users;
                std::vector<audit_log_entry> entries;
        };
    } // namespace models
} // namespace disccord

#endif /* _audit_logs_hpp_ */
