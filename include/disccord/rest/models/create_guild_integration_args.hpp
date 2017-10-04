#ifndef _create_guild_integration_args_hpp_
#define _create_guild_integration_args_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_guild_integration_args : public
                                                  disccord::models::model
            {
                public:
                    create_guild_integration_args(std::string type,
                                                  uint64_t id);
                    virtual ~create_guild_integration_args();

                    std::string get_type();
                    uint64_t get_id();

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value>& info
                    ) override;

                private:
                    std::string type;
                    uint64_t id;
            };
        }
    }
}

#endif /* _create_guild_integration_args_hpp_ */
