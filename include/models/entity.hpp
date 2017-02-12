#ifndef _entity_hpp_
#define _entity_hpp_

#include <json.h>

namespace disccord
{
    namespace models
    {
        template<typename T>
        class entity
        {
            public:
                entity();

                static entity<T> create(T id, bool attached);
                virtual ~entity();

                static entity<T> decode(web::json::value json, bool attached);

                T getId();
            
            protected:
                T id;
                bool attached;
        };
    }
}

#include <models/entity.tpp>
#endif /* _entity_hpp_ */