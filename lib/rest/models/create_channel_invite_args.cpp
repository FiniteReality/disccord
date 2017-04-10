#include <disccord/rest/models/create_channel_invite_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_channel_invite_args::create_channel_invite_args()
            { }

            create_channel_invite_args::~create_channel_invite_args()
            { }

            void create_channel_invite_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(max_age);
                encode_field(max_uses);
                encode_field(temporary);
                encode_field(unique);

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void create_channel_invite_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(max_age, uint32_t)
            define_set_method(max_uses, uint32_t)
            define_set_method(temporary, bool)
            define_set_method(unique, bool)

            #undef define_set_method
        }
    }
}
