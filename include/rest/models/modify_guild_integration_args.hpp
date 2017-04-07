#ifndef _modify_guild_integration_args_hpp_
#define _modify_guild_integration_args_hpp_

#include <models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_guild_integration_args : public disccord::models::model
            {
                public:
                    modify_guild_integration_args(uint32_t expire_behavior, uint32_t expire_grace_period, bool enable_emoticons);
                    virtual ~modify_guild_integration_args();

                    uint32_t get_expire_behavior();
                    uint32_t get_expire_grace_period();
                    bool get_enable_emoticons();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    uint32_t expire_behavior, expire_grace_period;
                    bool enable_emoticons;
            };
        }
    }
}

#endif /* _modify_guild_integration_args_hpp_ */
