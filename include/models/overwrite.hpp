#ifndef _overwrite_hpp_
#define _overwrite_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class overwrite : public model
        {
            public:
                overwrite();
                virtual ~overwrite();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                uint64_t get_allow();
                uint64_t get_deny();
                std::string get_type();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id, allow, deny;
                std::string type;
        };
    }
}

#endif /* _overwrite_hpp_ */
