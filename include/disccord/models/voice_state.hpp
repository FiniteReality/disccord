#ifndef _voice_state_hpp_
#define _voice_state_hpp_

#include <disccord/models/entity.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace models
    {
        class voice_state : public model
        {
            public:
                voice_state();
                virtual ~voice_state();

                virtual void decode(web::json::value json) override;

                util::optional<uint64_t> get_guild_id();
                uint64_t get_channel_id();
                uint64_t get_user_id();
                std::string get_session_id();
                bool get_deaf();
                bool get_mute();
                bool get_self_deaf();
                bool get_self_mute();
                bool get_suppress();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<uint64_t> guild_id;
                uint64_t channel_id, user_id;
                std::string session_id;
                bool deaf, mute, self_deaf, self_mute, suppress;
        };
    }
}

#endif /* _voice_state_hpp_ */
