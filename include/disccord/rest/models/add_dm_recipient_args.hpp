#ifndef _add_dm_recipient_args_hpp_
#define _add_dm_recipient_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/models/embed.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class add_dm_recipient_args : public disccord::models::model
            {
                public:
                    add_dm_recipient_args(std::string access_token,
                                          std::string nick);
                    virtual ~add_dm_recipient_args();

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value>& info
                    ) override;

                private:
                    std::string access_token, nick;
            };
        }
    }
}

#endif /* _add_dm_recipient_args_hpp_ */
