#ifndef _add_guild_member_args_hpp_
#define _add_guild_member_args_hpp_

#include <models/model.hpp>
#include <util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class add_guild_member_args : public disccord::models::model
            {
                public:
                    add_guild_member_args(std::string access_token);
                    virtual ~add_guild_member_args();

                    void set_nick(std::string nick);
                    void set_roles(std::vector<uint64_t> roles);
                    void set_mute(bool mute);
                    void set_deaf(bool deaf);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string access_token;
                    util::optional<std::string> nick;
                    util::optional<std::vector<uint64_t>> roles;
                    util::optional<bool> mute, deaf;
            };
        }
    }
}

#endif /* _add_guild_member_args_hpp_ */
