#ifndef _task_sleep_hpp_
#define _task_sleep_hpp_

#include <pplx/pplxtasks.h>

namespace disccord
{
    namespace util
    {
        pplx::task<void> task_sleep(const double s);
    } // namespace util
} // namespace disccord

#endif /* _task_sleep_hpp_ */
