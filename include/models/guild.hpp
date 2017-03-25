#ifndef _guild_hpp_
#define _guild_hpp_

#include <vector>

#include <models/entity.hpp>
#include <models/role.hpp>
#include <models/emoji.hpp>
#include <models/guild_member.hpp>
#include <models/channel.hpp>
#include <models/presence.hpp>
//#include <models/voice_state.hpp>

namespace disccord
{
    namespace models
    {
        class guild : public entity
        {
            public:
                guild();
                virtual ~guild();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                util::optional<std::string> get_icon();
                util::optional<std::string> get_splash();
                uint64_t get_owner_id();
                std::string get_region();
                util::optional<uint64_t> get_afk_channel_id();
                int32_t get_afk_timeout();
                int32_t get_mfa_level();
                int32_t get_verification_level();
                int32_t get_default_message_notifications();
                bool get_embed_enabled();
                util::optional<uint64_t> get_embed_channel_id();
                // TODO: voice states
                std::vector<std::string> get_features();
                util::optional<std::vector<role>> get_roles();
                util::optional<std::vector<emoji>> get_emojis();
                util::optional<std::vector<guild_member>> get_members();
                util::optional<std::vector<channel>> get_channels();
                util::optional<std::vector<presence>> get_presences();

            protected:
                virtual void encode_to(std::unordered_map<std::string,web::json::value> &info) override;

            private:
                std::string name, region;
                util::optional<std::string> icon, splash;
                uint64_t owner_id;
                util::optional<uint64_t> afk_channel_id, embed_channel_id;
                int32_t afk_timeout, mfa_level, verification_level, default_message_notifications;
                bool embed_enabled;
                std::vector<std::string> features;
                util::optional<std::vector<role>> roles;
                util::optional<std::vector<emoji>> emojis;
                util::optional<std::vector<guild_member>> members;
                util::optional<std::vector<channel>> channels;
                util::optional<std::vector<presence>> presences;
        };
    }
}

#endif /* _guild_hpp_ */
