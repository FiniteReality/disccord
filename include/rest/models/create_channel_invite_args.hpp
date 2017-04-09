#ifndef _create_channel_invite_args_hpp_
#define _create_channel_invite_args_hpp_

#include <models/model.hpp>
#include <util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_channel_invite_args : public disccord::models::model
            {
                public:
                    create_channel_invite_args();
                    virtual ~create_channel_invite_args();

                    void set_max_age(uint32_t max_age);
                    void set_max_uses(uint32_t max_uses);
                    void set_temporary(bool temporary);
                    void set_unique(bool unique);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<uint32_t> max_age, max_uses;
                    util::optional<bool> temporary, unique;
            };
        }
    }
}

#endif /* _create_channel_invite_args_hpp_ */

