#ifndef _modify_current_nick_args_hpp_
#define _modify_current_nick_args_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_current_nick_args : public disccord::models::model
            {
                public:
                    modify_current_nick_args(std::string nick);
                    virtual ~modify_current_nick_args();

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value>& info
                    ) override;

                private:
                    std::string nick;
            };
        }
    }
}

#endif /* _modify_current_nick_args_hpp_ */
