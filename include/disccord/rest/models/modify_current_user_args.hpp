#ifndef _modify_current_user_args_hpp_
#define _modify_current_user_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_current_user_args : public disccord::models::model
            {
                public:
                    modify_current_user_args();
                    virtual ~modify_current_user_args();

                    void set_name(std::string name);
                    void set_avatar(std::string avatar);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> name, avatar; //avatar must be passed image data converted to base64 data
            };
        }
    }
}

#endif /* _modify_current_user_args_hpp_ */
