#ifndef _bucket_info_hpp_
#define _bucket_info_hpp_

#include <cpprest/http_client.h>

#include <util/semaphore.hpp>

#include <string>

namespace disccord
{
    namespace api
    {
        class bucket_info
        {
            public:
                bucket_info(std::string method);
                virtual ~bucket_info();

                pplx::task<web::http::http_response> enter(web::http::client::http_client& client,
                    web::http::http_request& request, 
                    pplx::cancellation_token token = pplx::cancellation_token::none());

            private:
                void parse_headers(web::http::http_headers headers);

                std::string http_method;
                disccord::util::semaphore entry_semaphore;
                uint64_t reset_in;
        };
    }
}


#endif /* _bucket_info_hpp_ */
