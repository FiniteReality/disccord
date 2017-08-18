#include <disccord/util/task_sleep.hpp>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace disccord
{
    namespace util
    {
        pplx::task<void> task_sleep(const double s)
        {
            pplx::task_completion_event<void> tce;
            // async timer
            boost::asio::io_service io;
            boost::asio::deadline_timer t(io, boost::posix_time::seconds(s));
            t.async_wait([&tce](const boost::system::error_code& err){
                if (err)
                    tce.set_exception(std::runtime_error(err.message()));
                else
                    tce.set();
            });
            io.run();
            return pplx::create_task(tce);
        }
    } // namespace util
} // namespace disccord
