#include <disccord/rest/models/modify_guild_member_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_member_args::modify_guild_member_args()
            { }

            modify_guild_member_args::~modify_guild_member_args()
            { }

            void modify_guild_member_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {

                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(channel_id);
                encode_field(nick);
                encode_field(mute);
                encode_field(deaf);
                if (roles.is_specified())
                {
                    auto _roles = roles.get_value();
                    std::vector<web::json::value> roles_array(_roles.size());
                    std::transform(_roles.begin(), _roles.end(), roles_array.begin(), [](uint64_t role)
                        {
                            return web::json::value(std::to_string(role));
                        });
                    info["roles"] = web::json::value::array(roles_array);
                }

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void modify_guild_member_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(channel_id, uint64_t)
            define_set_method(nick, std::string)
            define_set_method(mute, bool)
            define_set_method(deaf, bool)
            define_set_method(roles, std::vector<uint64_t>)

            #undef define_set_method
        }
    }
}
