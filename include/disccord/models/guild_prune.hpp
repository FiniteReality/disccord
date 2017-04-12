#ifndef _guild_prune_hpp_
#define _guild_prune_hpp_

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace models
    {
        class guild_prune : public model
        {
            public:
                guild_prune();
                virtual ~guild_prune();

                virtual void decode(web::json::value json) override;

                uint32_t get_days();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint32_t days;
        };
    }
}

#endif /* _guild_prune_hpp_ */
