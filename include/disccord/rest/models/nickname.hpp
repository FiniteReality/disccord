#ifndef _nickname_hpp_
#define _nickname_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class nickname : public disccord::models::model
            {
                public:
                    nickname();
                    virtual ~nickname();

                    virtual void decode(web::json::value json) override;

                    std::string get_nick();

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value> &info
                    ) override;

                private:
                    std::string nick;
            };
        }
    }
}

#endif /* _nickname_hpp_ */
