#ifndef _guild_member_hpp_
#define _guild_member_hpp_

#include <vector>

#include <disccord/models/entity.hpp>
#include <disccord/models/user.hpp>

namespace disccord
{
    namespace models
    {
        class guild_member : public model
        {
            public:
                guild_member();
                virtual ~guild_member();

                virtual void decode(web::json::value json) override;

                util::optional<models::user> get_member();
                util::optional<std::string> get_nick();
                util::optional<std::vector<uint64_t>> get_roles();
                std::string get_joined_at();
                bool get_deaf();
                bool get_mute();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<user> member;
                util::optional<std::string> nick;
                util::optional<std::vector<uint64_t>> roles;
                std::string joined_at;
                bool deaf, mute;
        };
    }
}

#endif /* _guild_member_hpp_ */
