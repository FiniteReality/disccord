#ifndef _create_group_dm_args_hpp_
#define _create_group_dm_args_hpp_

#include <unordered_map>
#include <vector>

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_group_dm_args : public disccord::models::model
            {
                public:
                    create_group_dm_args(std::unordered_map<uint64_t, std::string> nicks, std::vector<std::string> access_tokens);
                    virtual ~create_group_dm_args();

                    std::unordered_map<uint64_t, std::string> get_nicks();
                    std::vector<std::string> get_access_tokens();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::unordered_map<uint64_t, std::string> nicks;
                    std::vector<std::string> access_tokens;
            };
        }
    }
}

#endif /* _create_group_dm_args_hpp_ */
