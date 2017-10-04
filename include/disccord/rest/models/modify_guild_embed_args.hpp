#ifndef _modify_guild_embed_args_hpp_
#define _modify_guild_embed_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_guild_embed_args : public disccord::models::model
            {
                public:
                    modify_guild_embed_args();
                    virtual ~modify_guild_embed_args();

                    void set_enabled(bool enabled);
                    void set_channel_id(uint64_t channel_id);

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value>& info
                    ) override;

                private:
                    util::optional<bool> enabled;
                    util::optional<uint64_t> channel_id;
            };
        }
    }
}

#endif /* _modify_guild_embed_args_hpp_ */
