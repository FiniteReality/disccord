#ifndef _invite_guild_hpp_
#define _invite_guild_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class invite_guild : public model
        {
            public:
                invite_guild();
                virtual ~invite_guild();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                std::string get_name();
                util::optional<std::string> get_splash();
                util::optional<std::string> get_icon();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
                std::string name;
                util::optional<std::string> splash, icon;
        };
    }
}

#endif /* _invite_guild_hpp_ */
