#include <models/guild_member.hpp>

namespace disccord
{
    namespace models
    {
        guild_member::guild_member()
        : member(), nick(), roles(),
        joined_at(""), deaf(false), mute(false)
        { }

        guild_member::~guild_member()
        { }

        void guild_member::decode(web::json::value json)
        {
            joined_at = json.at("joined_at").as_string();
            deaf = json.at("deaf").as_bool();
            mute = json.at("mute").as_bool();

            #define get_field(var, conv) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(field.conv()); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_field(nick, as_string);

            if (json.has_field("user")) {
                auto field = json.at("user");
                if (!field.is_null()) {
                    user val;
                    val.decode(field);
                    member = util::optional<user>(val);
                } else {
                    member = util::optional<user>::no_value();
                }
            }
            else {
                member = util::optional<user>();
            }

            if (json.has_field("roles"))
            {
                auto _roles_array = json.at("roles").as_array();
                std::vector<uint64_t> roles_array(_roles_array.size());
                std::transform(_roles_array.begin(), _roles_array.end(), roles_array.begin(), [](web::json::value _role)
                    {
                        return std::stoull(_role.as_string());
                    });
                roles = roles_array;
            }

            #undef get_field
        }

        void guild_member::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["joined_at"] = web::json::value(joined_at);
            info["deaf"] = web::json::value(deaf);
            info["mute"] = web::json::value(mute);
            if (nick.is_specified())
                info["nick"] = web::json::value(nick.get_value());
            if (member.is_specified())
                info["user"] = member.get_value().encode();
            if (roles.is_specified())
            {
                auto _roles = get_roles().get_value();
                std::vector<web::json::value> roles_array(_roles.size());
                std::transform(_roles.begin(), _roles.end(), roles_array.begin(), [](uint64_t role)
                    {
                        return web::json::value(role);
                    });
                info["roles"] = web::json::value::array(roles_array);
            }
        }

        #define define_get_method(field_name) \
            decltype(guild_member::field_name) guild_member::get_##field_name() { \
                return field_name; \
            }

        define_get_method(joined_at)
        define_get_method(deaf)
        define_get_method(mute)
        define_get_method(nick)
        define_get_method(member)
        define_get_method(roles)

        #undef define_get_method
    }
}
