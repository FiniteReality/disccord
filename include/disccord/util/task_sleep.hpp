#ifndef _task_sleep_hpp_
#define _task_sleep_hpp_

#include <pplx/pplxtasks.h>

namespace disccord
{
    namespace pplxtra
    {
        namespace task
        {
           pplx::task<void> sleep(const int64_t millis);
        }
    }
}

#endif /* _task_sleep_hpp_ */
