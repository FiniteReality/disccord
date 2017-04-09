#ifndef _channel_hpp_
#define _channel_hpp_

#include <vector>

#include <models/entity.hpp>
#include <models/user.hpp>
#include <models/overwrite.hpp>

namespace disccord
{
    namespace models
    {
        class channel : public entity
        {
            public:
                channel();
                virtual ~channel();

                virtual void decode(web::json::value json) override;

                util::optional<uint64_t> get_last_message_id();
                util::optional<uint64_t> get_guild_id();
                util::optional<uint32_t> get_position();
                util::optional<uint32_t> get_bitrate();
                util::optional<uint32_t> get_user_limit();
                util::optional<std::string> get_name();
                util::optional<uint8_t> get_type();
                util::optional<std::string> get_topic();
                util::optional<bool> get_is_private();
                util::optional<user> get_recipient();
                util::optional<std::vector<overwrite>> get_permission_overwrites();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<uint64_t> guild_id, last_message_id;
                util::optional<uint32_t> position, bitrate, user_limit;
                util::optional<uint8_t> type;
                util::optional<std::string> name, topic;
                util::optional<bool> is_private;
                util::optional<user> recipient;
                util::optional<std::vector<overwrite>> permission_overwrites;

        };
    }
}

#endif /* _channel_hpp_ */
