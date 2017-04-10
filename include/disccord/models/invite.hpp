#ifndef _invite_hpp_
#define _invite_hpp_

#include <disccord/models/entity.hpp>
#include <disccord/models/invite_channel.hpp>
#include <disccord/models/invite_guild.hpp>

namespace disccord
{
    namespace models
    {
        class invite : public model
        {
            public:
                invite();
                virtual ~invite();

                virtual void decode(web::json::value json) override;

                std::string get_code();
                util::optional<invite_channel> get_channel();
                util::optional<invite_guild> get_guild();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string code;
                util::optional<invite_channel> channel;
                util::optional<invite_guild> guild;
        };
    }
}

#endif /* _invite_hpp_ */
