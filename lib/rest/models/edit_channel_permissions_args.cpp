#include <rest/models/edit_channel_permissions_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            edit_channel_permissions_args::edit_channel_permissions_args(uint32_t _allow, uint32_t _deny, std::string _type)
                : allow(_allow), deny(_deny), type(_type)
            { }

            edit_channel_permissions_args::~edit_channel_permissions_args()
            { }

            void edit_channel_permissions_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["allow"] = web::json::value(allow);
                info["deny"] = web::json::value(deny);
                info["type"] = web::json::value(type);
            }
        }
    }
}
