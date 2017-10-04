#include <disccord/rest/models/guild_role_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            guild_role_args::guild_role_args()
            { }

            guild_role_args::~guild_role_args()
            { }

            void guild_role_args::encode_to(
                std::unordered_map<std::string, web::json::value>& info)
            {

                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(permissions);
                encode_field(color);
                encode_field(name);
                encode_field(hoist);
                encode_field(mentionable);

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void guild_role_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(permissions, uint32_t)
            define_set_method(color, uint32_t)
            define_set_method(name, std::string)
            define_set_method(hoist, bool)
            define_set_method(mentionable, bool)

            #undef define_set_method
        }
    }
}
