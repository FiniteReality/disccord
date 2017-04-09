#include <rest/models/create_guild_channel_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            create_guild_channel_args::create_guild_channel_args(std::string _name)
            : name(_name)
            { }

            create_guild_channel_args::~create_guild_channel_args()
            { }

            void create_guild_channel_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["name"] = web::json::value(name);

                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(type);
                encode_field(bitrate);
                encode_field(user_limit);
                //TODO: permission_overwrites

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void create_guild_channel_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(type, uint8_t)
            define_set_method(bitrate, uint32_t)
            define_set_method(user_limit, uint32_t)
            //TODO: permission_overwrites

            #undef define_set_method
        }
    }
}
