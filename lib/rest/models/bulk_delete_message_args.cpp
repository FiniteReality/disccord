#include <disccord/rest/models/bulk_delete_message_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            bulk_delete_message_args::bulk_delete_message_args(std::vector<uint64_t> _message_ids)
            : message_ids(_message_ids)
            { }

            bulk_delete_message_args::~bulk_delete_message_args()
            { }

            void bulk_delete_message_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                auto _messages = message_ids;
                std::vector<web::json::value> messages_array(_messages.size());
                std::transform(_messages.begin(), _messages.end(), messages_array.begin(), [](uint64_t message)
                    {
                        return web::json::value(message);
                    });
                info["messages"] = web::json::value::array(messages_array);
            }
        }
    }
}
