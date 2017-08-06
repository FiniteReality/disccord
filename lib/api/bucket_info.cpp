#include <exception>

#include <disccord/api/bucket_info.hpp>

namespace disccord
{
    namespace api
    {
        bucket_info::bucket_info(const std::string& method)
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
                throw new std::runtime_error("encountered a global ratelimit");
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

        pplx::task<web::http::http_response> bucket_info::enter(web::http::client::http_client& client, disccord::api::request_info* info, const pplx::cancellation_token& token)
        {
            return entry_semaphore.enter().then([this,&client,info,&token](bool success)
            {
                if (!success)
                    throw new std::runtime_error("failed to enter semaphore");

                web::http::http_request request(info->get_method());
                request.set_request_uri(info->get_url());
                if (info->get_has_body())
                {
                    request.set_body(info->get_body(), info->get_content_type());
                }

                auto headers = request.headers();
                for (auto& pair : info->get_headers())
                {
                    headers.add(pair.first, pair.second);
                }

                auto req = client.request(request, token);
                return req;
            }).then([this,info](web::http::http_response response) mutable -> web::http::http_response
            {
                // only delete the request info once the request has completed to prevent memory corruption
                delete info;
                // TODO: assert result was successful
                parse_headers(response.headers());
                entry_semaphore.release();
                return response;
            });
        }
    }
}
