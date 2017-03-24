#include <api/bucket_info.hpp>

#include <exception>

namespace disccord
{
    namespace api
    {
        bucket_info::bucket_info(std::string method)
            : http_method(method), entry_semaphore(1)
        { }

        bucket_info::~bucket_info()
        { }

        void bucket_info::parse_headers(web::http::http_headers headers)
        {
            // HACK: this code is in *no* way complete!

            std::string global = headers["X-RateLimit-Global"];
            std::string limit = headers["X-RateLimit-Limit"];
            std::string remaining = headers["X-RateLimit-Remaining"];
            std::string reset = headers["X-RateLimit-Reset"];
            std::string retry_after = headers["Retry-After"];

            if (global == "true")
            {
                // TODO: handle global ratelimits
                throw new std::runtime_error("We encountered a global ratelimit :(");
            }
            else if (limit.empty() || remaining.empty() || reset.empty() || retry_after.empty())
            {
                // No ratelimit information
                entry_semaphore.set_maximum_count(5); // Set a sensible limit for safety
            }
            else
            {
                utility::datetime date = utility::datetime::from_string(headers.date());

                reset_in = (date - std::stoull(reset)).to_interval();
                entry_semaphore.set_maximum_count(std::stoi(limit));
            }
        }

        pplx::task<web::http::http_response> bucket_info::enter(web::http::client::http_client& client, web::http::http_request& request, pplx::cancellation_token token)
        {
            return entry_semaphore.enter().then([this,&client,&request,&token](bool success){
                return client.request(request, token);
            }).then([this](web::http::http_response response){
                // TODO: assert result was successful
                parse_headers(response.headers());
                return response;
            });
        }
    }
}
