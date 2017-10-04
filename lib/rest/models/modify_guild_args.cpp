#include <disccord/rest/models/modify_guild_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_args::modify_guild_args()
            { }

            modify_guild_args::~modify_guild_args()
            { }

            void modify_guild_args::encode_to(
                std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(name);
                encode_field(region);
                encode_field(icon);
                encode_field(splash);
                encode_field(afk_channel_id);
                encode_field(owner_id);
                encode_field(verification_level);
                encode_field(default_message_notifications);
                encode_field(afk_timeout);

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void modify_guild_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(name, std::string)
            define_set_method(region, std::string)
            define_set_method(icon, std::string)
            define_set_method(splash, std::string)
            define_set_method(afk_channel_id, uint64_t)
            define_set_method(owner_id, uint64_t)
            define_set_method(verification_level, uint32_t)
            define_set_method(default_message_notifications, uint32_t)
            define_set_method(afk_timeout, uint32_t)

            #undef define_set_method
        }
    }
}
