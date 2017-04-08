#ifndef _edit_channel_permissions_args_hpp_
#define _edit_channel_permissions_args_hpp_

#include <models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class edit_channel_permissions_args : public disccord::models::model
            {
                public:
                    edit_channel_permissions_args(uint32_t allow, uint32_t deny, std::string type);
                    virtual ~edit_channel_permissions_args();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    uint32_t allow, deny;
                    std::string type;
            };
        }
    }
}

#endif /* _edit_channel_permissions_args_hpp_ */
