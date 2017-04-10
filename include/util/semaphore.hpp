#ifndef _semaphore_hpp_
#define _semaphore_hpp_

#include <atomic>
#include <mutex>
#include <condition_variable>

#include <pplx/pplxtasks.h>

namespace disccord
{
    namespace util
    {
        class semaphore
        {
            public:
                semaphore(int maximum_count);

                virtual ~semaphore();

                int get_current_count();
                void set_maximum_count(int new_maximum);

                pplx::task<bool> enter();
                pplx::task<bool> enter(int timeout_millis);

                void release();

            private:
                int current_count;
                std::atomic_int maximum_count;

                std::mutex entry_mutex;
                std::condition_variable entry_condition;
        };
    }
}

#endif /* _semaphore_hpp_ */
