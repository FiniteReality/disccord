#include <boost/lexical_cast.hpp>

#include <disccord/models/user.hpp>

namespace disccord
{
    namespace models
    {
        user::user()
            : username(""), avatar(), email(), discriminator(0),
            bot(false), mfa_enabled(), verified()
        { }

        user::~user()
        { }

        void user::decode(web::json::value json)
        {
            entity::decode(json);

            username = json.at("username").as_string();
            // HACK: use boost::lexical_cast here since it safely
            // validates values
            auto str_js = json.at("discriminator");
            discriminator = boost::lexical_cast<uint16_t>(str_js.as_string());

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

            get_field(avatar, as_string);
            bot = json.at("bot").as_bool();
            //get_field(bot, as_bool);
            get_field(mfa_enabled, as_bool);
            get_field(verified, as_bool);
            get_field(email, as_string);

            #undef get_field
        }

        void user::encode_to(std::unordered_map<std::string,
                                                web::json::value> &info)
        {
            entity::encode_to(info);

            info["username"] = web::json::value(get_username());
            info["discriminator"] =
                web::json::value(std::to_string(get_discriminator()));
            if (get_avatar().is_specified())
                info["avatar"] = get_avatar();
            info["bot"] = web::json::value(get_bot());
            if (get_mfa_enabled().is_specified())
                info["mfa_enabled"] = get_mfa_enabled();
            if (get_verified().is_specified())
                info["verified"] = get_verified();
            if (get_email().is_specified())
                info["email"] = get_email();
        }

        #define define_get_method(field_name) \
            decltype(user::field_name) user::get_##field_name() { \
                return field_name; \
            }

        define_get_method(username)
        define_get_method(discriminator)
        define_get_method(avatar)
        define_get_method(bot)
        define_get_method(mfa_enabled)
        define_get_method(verified)
        define_get_method(email)
        
        util::optional<std::string> user::get_avatar_url()
        {
            if (get_avatar().is_specified())
            {
                std::string url = "https://cdn.discordapp.com/avatars/" + 
                                  std::to_string(get_id()) + "/" +
                                  get_avatar().get_value()+".png?size=1024";
                return util::optional<std::string>(url);
            }
            else
                return util::optional<std::string>::no_value();
        }

        #undef define_get_method
    }
}
