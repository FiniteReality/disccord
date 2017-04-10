#ifndef _modify_guild_member_args_hpp_
#define _modify_guild_member_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_guild_member_args : public disccord::models::model
            {
                public:
                    modify_guild_member_args();
                    virtual ~modify_guild_member_args();

                    void set_channel_id(uint64_t channel_id);
                    void set_nick(std::string nick);
                    void set_roles(std::vector<uint64_t> roles);
                    void set_mute(bool mute);
                    void set_deaf(bool deaf);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<uint64_t> channel_id;
                    util::optional<std::string> nick;
                    util::optional<std::vector<uint64_t>> roles;
                    util::optional<bool> mute, deaf;
            };
        }
    }
}

#endif /* _modify_guild_member_args_hpp_ */
