#ifndef _entity_hpp_
#define _entity_hpp_

#include <string>
#include <unordered_map>
#include <cstdint>

#include <disccord/util/optional.hpp>
#include <disccord/models/model.hpp>

namespace disccord
{
    namespace models
    {
        class entity : public model
        {
            public:
                entity();
                virtual ~entity();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
        };
    }
}

#endif /* _entity_hpp_ */
