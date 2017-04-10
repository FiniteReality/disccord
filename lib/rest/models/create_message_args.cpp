#include <disccord/rest/models/create_message_args.hpp>

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
                info["content"] = web::json::value(content);
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(nonce);
                encode_field(tts);
                if (embed.is_specified())
                    info["embed"] = embed.get_value().encode();

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void create_message_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(nonce, uint64_t)
            define_set_method(tts, bool)
            define_set_method(embed, disccord::models::embed)

            #undef define_set_method
        }
    }
}
