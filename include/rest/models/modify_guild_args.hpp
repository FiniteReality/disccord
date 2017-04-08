#ifndef _modify_guild_args_hpp_
#define _modify_guild_args_hpp_

#include <models/model.hpp>
#include <util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_guild_args : public disccord::models::model
            {
                public:
                    modify_guild_args();
                    virtual ~modify_guild_args();

                    void set_name(std::string name);
                    void set_region(std::string region);
                    void set_icon(std::string icon);
                    void set_splash(std::string splash);
                    void set_afk_channel_id(uint64_t afk_channel_id);
                    void set_owner_id(uint64_t owner_id);
                    void set_verification_level(uint32_t verification_level);
                    void set_default_message_notifications(uint32_t default_message_notifications);
                    void set_afk_timeout(uint32_t afk_timeout);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> name, region, icon, splash;
                    util::optional<uint64_t> afk_channel_id, owner_id;
                    util::optional<uint32_t> verification_level, default_message_notifications, afk_timeout;
            };
        }
    }
}

#endif /* _modify_guild_args_hpp_ */
