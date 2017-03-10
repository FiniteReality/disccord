#ifndef _guild_hpp_
#define _guild_hpp_

#include <models/entity.hpp>
#include <vector>

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
                bool get_embed_enabled();
                util::optional<uint64_t> get_embed_channel_id();
                // TODO: verification level
                // TODO: voice states
                // TODO: roles
                // TODO: emojis
                std::vector<std::string> get_features();
                // TODO: mfa level
                // TODO: default mesasge notifs

            protected:
                virtual void encode_to(std::unordered_map<std::string,web::json::value> &info) override;

            private:
                std::string name, region;
                util::optional<std::string> icon, splash;
                uint64_t owner_id;
                util::optional<uint64_t> afk_channel_id, embed_channel_id;
                int32_t afk_timeout;
                bool embed_enabled;
                std::vector<std::string> features;
        };
    }
}

#endif /* _guild_hpp_ */
