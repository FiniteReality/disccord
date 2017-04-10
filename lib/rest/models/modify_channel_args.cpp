#include <disccord/rest/models/modify_channel_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_channel_args::modify_channel_args()
            { }

            modify_channel_args::~modify_channel_args()
            { }

            void modify_channel_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(name);
                encode_field(topic);
                encode_field(position);
                encode_field(user_limit);
                encode_field(bitrate);
                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void modify_channel_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(name, std::string)
            define_set_method(topic, std::string)
            define_set_method(position, uint16_t)
            define_set_method(user_limit, uint16_t)
            define_set_method(bitrate, uint32_t)

            #undef define_set_method
        }
    }
}
