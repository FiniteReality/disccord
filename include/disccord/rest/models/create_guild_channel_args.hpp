#ifndef _create_guild_channel_args_hpp_
#define _create_guild_channel_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>
#include <disccord/models/overwrite.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_guild_channel_args : public disccord::models::model
            {
                public:
                    create_guild_channel_args(std::string name);
                    virtual ~create_guild_channel_args();

                    void set_type(uint8_t type);
                    void set_bitrate(uint32_t bitrate);
                    void set_user_limit(uint32_t user_limit);
                    void set_permission_overwrites(std::vector<disccord::models::overwrite> permission_overwrites);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string name;
                    util::optional<uint8_t> type;
                    util::optional<uint32_t> bitrate, user_limit;
                    util::optional<std::vector<disccord::models::overwrite>> permission_overwrites;
            };
        }
    }
}

#endif /* _create_guild_channel_args_hpp_ */
