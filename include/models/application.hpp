#ifndef _application_hpp_
#define _application_hpp_

#include <models/entity.hpp>
#include <models/user.hpp>

namespace disccord
{
    namespace models
    {
        class application : public entity
        {
            public:
                application();
                virtual ~application();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                std::string get_name();
                util::optional<std::string> get_icon();
                util::optional<std::string> get_description();
                util::optional<std::vector<std::string>> get_rpc_origins();
                bool get_bot_public();
                bool get_bot_requires_code_grant();
                util::optional<user> get_owner();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
                std::string name;
                util::optional<std::string> icon, description;
                util::optional<std::vector<std::string>> rpc_origins;
                bool bot_public, bot_requires_code_grant;
                util::optional<user> owner;
                
        };
    }
}

#endif /* _application_hpp_ */
