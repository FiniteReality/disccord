#ifndef _user_hpp_
#define _user_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class user : public entity
        {
            public:
                user();
                virtual ~user();

                virtual void decode(web::json::value json) override;

                std::string get_username();
                uint16_t get_discriminator();
                util::optional<std::string> get_avatar();
                util::optional<std::string> get_avatar_url();
                bool get_bot();
                util::optional<bool> get_mfa_enabled();
                util::optional<bool> get_verified();
                util::optional<std::string> get_email();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string username;
                util::optional<std::string> avatar, email, avatar_url;
                uint16_t discriminator;
                bool bot;
                util::optional<bool> mfa_enabled, verified;
        };
    }
}

#endif /* _user_hpp_ */
