#include <string>
#include <algorithm>
#include <utility>

#include <rest/models/create_group_dm_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_group_dm_args::create_group_dm_args(std::unordered_map<uint64_t, std::string> nicknames, std::vector<std::string> tokens)
                : nicks(nicknames), access_tokens(tokens)
            { }

            create_group_dm_args::~create_group_dm_args()
            { }

            void create_group_dm_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                auto _access_tokens = get_access_tokens();
                std::vector<web::json::value> _tokens(_access_tokens.size());
                std::transform(_access_tokens.begin(), _access_tokens.end(), _tokens.begin(),
                    [](std::string token){
                        return web::json::value(token);
                    });
                web::json::value tokens = web::json::value::array(_tokens);

                auto _nicks = get_nicks();
                std::vector<std::pair<std::string, web::json::value>> _nicknames(_nicks.size());
                std::transform(_nicks.begin(), _nicks.end(), _nicknames.begin(), 
                    [](std::pair<uint64_t, std::string> field){
                        return std::make_pair(std::to_string(field.first), web::json::value(field.second));
                    });
                web::json::value nicknames = web::json::value::object(_nicknames);

                info["access_tokens"] = tokens;
                info["nicks"] = nicknames;
            }

            std::unordered_map<uint64_t, std::string> create_group_dm_args::get_nicks()
            {
                return nicks;
            }

            std::vector<std::string>  create_group_dm_args::get_access_tokens()
            {
                return access_tokens;
            }
        }
    }
}
