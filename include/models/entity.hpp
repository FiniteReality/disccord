#ifndef _entity_hpp_
#define _entity_hpp_

#include <util/optional.hpp>

#include <string>
#include <unordered_map>
#include <cstdint>

#include <json.h>

namespace disccord
{
    namespace models
    {
        class entity
        {
            public:
                entity();
                virtual ~entity();

                virtual void decode(web::json::value json);
                web::json::value encode();

                uint64_t get_id();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info);

            private:
                uint64_t id;
        };
    }
}

#endif /* _entity_hpp_ */