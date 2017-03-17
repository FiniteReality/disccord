#ifndef _integration_account_hpp_
#define _integration_account_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class integration_account : public entity
        {
            public:
                integration_account();
                virtual ~integration_account();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                std::string get_name();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
                std::string name;
        };
    }
}

#endif /* _integration_account_hpp_ */
