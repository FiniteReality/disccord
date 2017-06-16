#ifndef _audit_log_entry_hpp_
#define _audit_log_entry_hpp_

#include <disccord/models/entity.hpp>
#include <disccord/models/audit_log_change.hpp>
#include <disccord/models/audit_log_action_type.hpp>

namespace disccord
{
    namespace models
    {
        class audit_log_entry : public entity
        {
            public:
                audit_log_entry();
                virtual ~audit_log_entry();

                virtual void decode(web::json::value json) override;

                util::optional<uint64_t> get_target_id();
                uint64_t get_user_id();
                audit_log_action_type get_action_type();
                util::optional<std::vector<audit_log_change>> get_changes();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<uint64_t> target_id;
                uint64_t user_id;
                audit_log_action_type action_type;
                util::optional<std::vector<audit_log_change>> changes;
        };
    } // namespace models
} // namespace disccord

#endif /* _audit_log_entry_hpp_ */
