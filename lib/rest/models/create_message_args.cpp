#include <rest/models/create_message_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_message_args::create_message_args(std::string _content)
                : content(_content)
            { }

            create_message_args::~create_message_args()
            { }

            void create_message_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["content"] = web::json::value(get_content());
            }

            std::string create_message_args::get_content()
            {
                return content;
            }
        }
    }
}
