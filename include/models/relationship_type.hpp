#ifndef _relationship_type_hpp_
#define _relationship_type_hpp_

namespace disccord
{
    namespace models
    {
        enum class relationship_type {
            Friend = 1,
            Blocked = 2,
            IncomingPending = 3,
            OutgoingPending = 4
        };
    }
}

#endif /* _relationship_type_hpp_ */
