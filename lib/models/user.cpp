#include <boost/lexical_cast.hpp>

#include <models/user.hpp>

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

            // will never throw exceptions
            username = json.at("username").as_string();
            discriminator = boost::lexical_cast<uint16_t>(json.at("discriminator").as_string());

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
            // TODO: transition this to use the macro
            bot = json.at("bot").as_bool();
            get_field(mfa_enabled, as_bool);
            get_field(verified, as_bool);
            get_field(email, as_string);

            #undef get_field
        }

        void user::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["username"] = web::json::value(get_username());
            info["discriminator"] = web::json::value(std::to_string(get_discriminator()));
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

        std::string user::get_username()
        {
            return username;
        }
        uint16_t user::get_discriminator()
        {
            return discriminator;
        }
        util::optional<std::string> user::get_avatar()
        {
            return avatar;
        }
        bool user::get_bot()
        {
            return bot;
        }
        util::optional<bool> user::get_mfa_enabled()
        {
            return mfa_enabled;
        }
        util::optional<bool> user::get_verified()
        {
            return verified;
        }
        util::optional<std::string> user::get_email()
        {
            return email;
        }
    }
}