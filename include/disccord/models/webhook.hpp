#ifndef _webhook_hpp_
#define _webhook_hpp_

#include <disccord/models/entity.hpp>
#include <disccord/models/user.hpp>

namespace disccord
{
    namespace models
    {
        class webhook : public entity
        {
            public:
                webhook();
                virtual ~webhook();

                virtual void decode(web::json::value json) override;

                util::optional<uint64_t> get_guild_id();
                uint64_t get_channel_id();
                util::optional<models::user> get_user();
                util::optional<std::string> get_name();
                util::optional<std::string> get_avatar();
                std::string get_token();

            protected:
                virtual void encode_to(std::unordered_map<std::string,web::json::value> &info) override;

            private:
                util::optional<uint64_t> guild_id;
                uint64_t channel_id;
                util::optional<models::user> user;
                util::optional<std::string> name, avatar;
                std::string token;
        };
    }
}

#endif /* _webhook_hpp_ */
