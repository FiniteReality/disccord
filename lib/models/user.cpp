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
            bot = json.at("bot").as_bool();
            //get_field(bot, as_bool);
            get_field(mfa_enabled, as_bool);
            get_field(verified, as_bool);
            get_field(email, as_string);

            #undef get_field
        }

        void user::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["username"] = web::json::value(username);
            info["discriminator"] = web::json::value(std::to_string(discriminator));
            if (avatar.is_specified())
                info["avatar"] = web::json::value(avatar.get_value());
            info["bot"] = web::json::value(bot);
            if (mfa_enabled.is_specified())
                info["mfa_enabled"] = web::json::value(mfa_enabled.get_value());
            if (verified.is_specified())
                info["verified"] = web::json::value(verified.get_value());
            if (email.is_specified())
                info["email"] = web::json::value(email.get_value());
        }

        #define define_get_method(field_name) \
            decltype(user::field_name) user::get_##field_name() { \
                return field_name; \
            }

        define_get_method(username);
        define_get_method(discriminator);
        define_get_method(avatar);
        define_get_method(bot);
        define_get_method(mfa_enabled);
        define_get_method(verified);
        define_get_method(email);

        #undef define_get_method
    }
}
