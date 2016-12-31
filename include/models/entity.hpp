#ifndef _entity_hpp_
#define _entity_hpp_

namespace disccord
{
    namespace models
    {
        template<typename T>
        class entity
        {
            public:
                entity(T id, bool attached)
                virtual ~entity();

                T getId();
            
            protected:
                T id;
                bool attached;
        };
    }
}

#include <entity.tpp>
#endif /* _entity_hpp_ */