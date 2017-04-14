#include <disccord/rest/models/modify_current_nick_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_current_nick_args::modify_current_nick_args(std::string _nick)
                : nick(_nick)
            { }

            modify_current_nick_args::~modify_current_nick_args()
            { }

            void modify_current_nick_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["nick"] = web::json::value(nick);
            }
        }
    }
}
