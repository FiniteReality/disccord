#ifndef _create_guild_ban_args_hpp_
#define _create_guild_ban_args_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_guild_ban_args : public disccord::models::model
            {
                public:
                    create_guild_ban_args(uint8_t delete_message_days);
                    virtual ~create_guild_ban_args();

                    uint8_t get_delete_message_days();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    uint8_t delete_message_days;
            };
        }
    }
}

#endif /* _create_guild_ban_args_hpp_ */
