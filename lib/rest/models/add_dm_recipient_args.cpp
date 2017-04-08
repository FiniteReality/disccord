#include <rest/models/add_dm_recipient_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            add_dm_recipient_args::add_dm_recipient_args(std::string _access_token, std::string _nick)
                : access_token(_access_token), nick(_nick)
            { }

            add_dm_recipient_args::~add_dm_recipient_args()
            { }

            void add_dm_recipient_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["access_token"] = web::json::value(access_token);
                info["nick"] = web::json::value(nick);
            }
        }
    }
}
