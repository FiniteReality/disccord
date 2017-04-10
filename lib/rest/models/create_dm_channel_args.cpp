#include <disccord/rest/models/create_dm_channel_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_dm_channel_args::create_dm_channel_args(uint64_t recipient)
                : recipient_id(recipient)
            { }

            create_dm_channel_args::~create_dm_channel_args()
            { }

            void create_dm_channel_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["recipient_id"] = web::json::value(get_recipient_id());
            }

            uint64_t create_dm_channel_args::get_recipient_id()
            {
                return recipient_id;
            }
        }
    }
}
