#ifndef _bucket_info_hpp_
#define _bucket_info_hpp_

#include <cpprest/http_client.h>

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

                pplx::task<bool> enter(web::http::client::http_client& client, std::string url);
        };
    }
}


#endif /* _bucket_info_hpp_ */