#ifndef _bucket_hpp_
#define _bucket_hpp_

#include <pplx/pplxtasks.h>

#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace disccord
{
    namespace api
    {
        class bucket_info
        {
            public:
                bucket_info(std::string bucket_url);
                virtual ~bucket_info();

                pplx::task<void> enter();
        };
    }
}


#endif /* _bucket_hpp_ */