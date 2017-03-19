#ifndef _integration_hpp_
#define _integration_hpp_

#include <models/entity.hpp>
#include <models/user.hpp>
#include <models/integration_account.hpp>

namespace disccord
{
    namespace models
    {
        class integration : public entity
        {
            public:
                integration();
                virtual ~integration();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                uint64_t get_role_id();
                std::string get_synced_at();
                std::string get_name();
                std::string get_type();
                uint32_t get_expire_behavior();
                uint32_t get_expire_grace_period();
                bool get_enabled();
                bool get_syncing();
                util::optional<models::user> get_user();
                util::optional<integration_account> get_account();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id, role_id;
                std::string name, type, synced_at;
                uint32_t expire_behavior, expire_grace_period;
                bool enabled, syncing;
                util::optional<models::user> user;
                util::optional<integration_account> account;
        };
    }
}

#endif /* _integration_hpp_ */
