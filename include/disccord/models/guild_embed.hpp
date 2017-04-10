#ifndef _guild_embed_hpp_
#define _guild_embed_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class guild_embed : public model
        {
            public:
                guild_embed();
                virtual ~guild_embed();

                virtual void decode(web::json::value json) override;

                bool get_enabled();
                uint64_t get_channel_id();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                bool enabled;
                uint64_t channel_id;
        };
    }
}

#endif /* _guild_embed_hpp_ */
