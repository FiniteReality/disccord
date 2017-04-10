#ifndef _presence_hpp_
#define _presence_hpp_

#include <vector>

#include <disccord/models/entity.hpp>
#include <disccord/models/game.hpp>
#include <disccord/models/user.hpp>

namespace disccord
{
    namespace models
    {
        class presence : public model
        {
            public:
                presence();
                virtual ~presence();

                virtual void decode(web::json::value json) override;

                util::optional<models::user> get_user();
                std::vector<uint64_t> get_roles();
                util::optional<models::game> get_game();
                uint64_t get_guild_id();
                std::string get_status();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<models::user> user;
                std::vector<uint64_t> roles;
                util::optional<models::game> game;
                uint64_t guild_id;
                std::string status;
        };
    }
}

#endif /* _presence_hpp_ */
