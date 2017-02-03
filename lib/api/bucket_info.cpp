#include <api/bucket_info.hpp>

namespace disccord
{
    namespace api
    {
        bucket_info::bucket_info(std::string bucket_url)
        { }

        bucket_info::~bucket_info()
        { }


        pplx::task<bool> bucket_info::enter(web::http::client::http_client& client, std::string url)
        {
            // check current count vs maximum count
            // update current count
            // request url
            // check headers + update maximum count
            // update current cont
            return pplx::create_task([]{ return false; });
        }
    }
}