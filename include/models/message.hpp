#ifndef _message_hpp_
#define _message_hpp_

#include <vector>

#include <models/entity.hpp>
#include <models/embed.hpp>
#include <models/user.hpp>
#include <models/role.hpp>
#include <models/attachment.hpp>
#include <models/reaction.hpp>

namespace disccord
{
    namespace models
    {
        class message : public entity
        {
            public:
                message();
                virtual ~message();

                virtual void decode(web::json::value json) override;

                util::optional<user> get_author();
                uint64_t get_id();
                uint64_t get_channel_id();
                std::string get_content();
                std::string get_timestamp();
                util::optional<std::string> get_edited_timestamp();
                util::optional<std::string> get_nonce();
                util::optional<std::string> get_webhook_id();
                bool get_tts();
                bool get_mention_everyone();
                bool get_pinned();
                util::optional<std::vector<user>> get_mentions();
                util::optional<std::vector<role>> get_mention_roles();
                util::optional<std::vector<attachment>> get_attachments();
                util::optional<std::vector<embed>> get_embeds();
                util::optional<std::vector<reaction>> get_reactions();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<user> author;
                uint64_t channel_id;
                std::string content, timestamp;
                util::optional<std::string> edited_timestamp, nonce, webhook_id;
                bool tts, mention_everyone, pinned;
                util::optional<std::vector<user>> mentions;
                util::optional<std::vector<role>> mention_roles;
                util::optional<std::vector<attachment>> attachments;
                util::optional<std::vector<embed>> embeds;
                util::optional<std::vector<reaction>> reactions;
        };
    }
}

#endif /* _message_hpp_ */
