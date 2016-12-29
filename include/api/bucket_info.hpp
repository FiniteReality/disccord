#ifndef _bucket_hpp_
#define _bucket_hpp_

#include <string>

namespace disccord
{
    namespace api
    {
        class bucket_info
        {
            public:
                bucket_info(std::string bucket_url);
                virtual ~bucket_info();
        };
    }
}


#endif /* _bucket_hpp_ */