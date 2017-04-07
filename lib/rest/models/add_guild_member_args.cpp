#include <rest/models/add_guild_member_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            add_guild_member_args::add_guild_member_args(std::string _access_token)
            : access_token(_access_token)
            { }
            
            add_guild_member_args::~add_guild_member_args()
            { }

            void add_guild_member_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                info["access_token"] = web::json::value(access_token);
                
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());
                        
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
                void add_guild_member_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }
            
            define_set_method(nick, std::string)
            define_set_method(mute, bool)
            define_set_method(deaf, bool)
            define_set_method(roles, std::vector<uint64_t>)
            
            #undef define_set_method
        }
    }
}
