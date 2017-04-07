#ifndef _modify_guild_args_hpp_
#define _modify_guild_args_hpp_

#include <models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_guild_args : public disccord::models::model
            {
                public:
                    modify_guild_args(std::string name);
                    virtual ~modify_guild_args();

                    std::string get_name();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string name;
            };
        }
    }
}

#endif /* _modify_guild_args_hpp_ */
