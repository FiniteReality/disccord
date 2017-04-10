#ifndef _create_dm_channel_args_hpp_
#define _create_dm_channel_args_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_dm_channel_args : public disccord::models::model
            {
                public:
                    create_dm_channel_args(uint64_t recipient_id);
                    virtual ~create_dm_channel_args();

                    uint64_t get_recipient_id();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    uint64_t recipient_id;
            };
        }
    }
}

#endif /* _create_dm_channel_args_hpp_ */
