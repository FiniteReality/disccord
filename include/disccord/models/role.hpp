#ifndef _role_hpp_
#define _role_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class role : public entity
        {
            public:
                role();
                virtual ~role();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                uint32_t get_color();
                uint32_t get_permissions();
                uint8_t get_position();
                bool get_managed();
                bool get_mentionable();
                bool get_hoist();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name;
                uint32_t color, permissions;
                uint8_t position;
                bool managed, mentionable, hoist;
        };
    }
}

#endif /* _role_hpp_ */
