#include <util/semaphore.hpp>

#include <limits>

namespace disccord
{
    namespace util
    {
        const int NO_TIMEOUT = -1;

        semaphore::semaphore(int maximum_count)
            : current_count{maximum_count}, maximum_count{maximum_count}
        { }

        semaphore::~semaphore() { }

        int semaphore::get_current_count()
        {
            return current_count;
        }

        void semaphore::set_maximum_count(int new_maximum)
        {
            maximum_count = new_maximum;
        }

        pplx::task<bool> semaphore::enter()
        {
            return enter(NO_TIMEOUT);
        }

        pplx::task<bool> semaphore::enter(int timeout_millis)
        {
            std::unique_lock<std::mutex> lock(entry_mutex);

            if (timeout_millis == 0 && current_count == 0)
            {
                return pplx::create_task([]{ return false; });
            }

            bool status = true;
            if (timeout_millis == NO_TIMEOUT)
            {
                entry_condition.wait(lock,
                    [=]{ return current_count > 0; });
            }
            else
            {
                status = entry_condition.wait_for(lock,
                    std::chrono::milliseconds(timeout_millis),
                    [=]{ return current_count > 0; });
            }

            if (!status)
            {
                // timed out while waiting
                return pplx::create_task([]{ return false; });
            }
            else
            {
                // we managed to get a lock
                --current_count;
                entry_condition.notify_all();

                return pplx::create_task([]{ return true; });
            }
        }

        void semaphore::release()
        {
            std::unique_lock<std::mutex> lock(entry_mutex);

            if (current_count < maximum_count)
                ++current_count;

            entry_condition.notify_all();
        }
    }
}