#include <disccord/util/task_sleep.hpp>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace disccord
{
    namespace pplxtra
    {
        namespace task
        {
            pplx::task<void> sleep(const int64_t millis)
            {
                pplx::task_completion_event<void> tce;

                boost::asio::io_service io;
                boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(millis));
                t.async_wait([&tce](const boost::system::error_code& err){
                    if (err)
                        tce.set_exception(std::runtime_error(err.message()));
                    else
                        tce.set();
                });
                io.run();

                return pplx::create_task(tce);
            }
        }
    }
}
