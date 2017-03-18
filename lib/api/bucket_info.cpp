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

        inline web::http::http_request create_request(std::string method, std::string url)
        {
            auto request = web::http::http_request(method);
            request.set_request_uri(url);

            return request;
        }
        
        inline web::http::http_request create_request(std::string method, std::string url, web::json::value body)
        {
            auto request = web::http::http_request(method);
            request.set_request_uri(url);
            request.set_body(body);

            return request;
        }

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

        pplx::task<web::json::value> bucket_info::request(web::http::client::http_client& client, std::string url, pplx::cancellation_token token)
        {
            if ((entry_semaphore.get_current_count() - 1) < 0)
            {
                // TODO: wait until the ratelimit is over
                throw std::runtime_error("pre-emptive ratelimit");
            }

            return entry_semaphore.enter().then([this,&client,url,token](bool success){
                auto request = create_request(http_method, url);
                return client.request(request, token);
            }).then([this](web::http::http_response response){
                // TODO: assert result was successful
                parse_headers(response.headers());
                return response.extract_json();
            });
        }
        
        pplx::task<web::json::value> bucket_info::request(web::http::client::http_client& client, std::string url, web::json::value body, pplx::cancellation_token token)
        {
            if ((entry_semaphore.get_current_count() - 1) < 0)
            {
                // TODO: wait until the ratelimit is over
                throw std::runtime_error("pre-emptive ratelimit");
            }

            return entry_semaphore.enter().then([this,&client,url,token,body](bool success){
                auto request = create_request(http_method, url, body);
                return client.request(request, token);
            }).then([this](web::http::http_response response){
                // TODO: assert result was successful
                parse_headers(response.headers());
                return response.extract_json();
            });
        }
    }
}