#include <rest/models/edit_message_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            edit_message_args::edit_message_args()
            { }

            edit_message_args::~edit_message_args()
            { }

            void edit_message_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(content);
                if (embed.is_specified())
                    info["embed"] = embed.get_value().encode();

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void edit_message_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(content, std::string)
            define_set_method(embed, disccord::models::embed)

            #undef define_set_method
        }
    }
}
