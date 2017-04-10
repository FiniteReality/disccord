#ifndef _user_guild_hpp_
#define _user_guild_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class user_guild : public entity
        {
            public:
                user_guild();
                virtual ~user_guild();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                std::string get_icon();
                bool get_owner();
                int64_t get_id();
                int64_t get_permissions();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name, icon;
                bool owner;
                int64_t id, permissions;
        };
    }
}

#endif /* _user_guild_hpp_ */
