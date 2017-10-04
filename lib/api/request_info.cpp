#include <disccord/api/request_info.hpp>

namespace disccord
{
    namespace api
    {
        request_info::request_info()
            : method("GET"),
              url(),
              headers(),
              has_body(false),
              body(""),
              body_content_type("")
        { }
        request_info::request_info(std::string r_method, web::uri r_url)
            : method(r_method),
              url(r_url),
              headers(),
              has_body(false),
              body(""),
              body_content_type("")
        { }

        request_info::~request_info()
        { }


        std::string request_info::get_method() const
        {
            return method;
        }

        web::uri request_info::get_url() const
        {
            return url;
        }

        std::unordered_map<std::string, std::string>
        request_info::get_headers() const
        {
            return headers;
        }

        bool request_info::get_has_body() const
        {
            return has_body;
        }

        std::string request_info::get_body() const
        {
            return body;
        }

        std::string request_info::get_content_type() const
        {
            return body_content_type;
        }


        void request_info::set_method(std::string r_method)
        {
            method = r_method;
        }

        void request_info::set_url(web::uri r_url)
        {
            url = r_url;
        }

        void request_info::set_header(std::string r_header,
                                      std::string r_value)
        {
            headers[r_header] = r_value;
        }

        void request_info::set_body(std::string r_body,
                                    std::string r_content_type)
        {
            has_body = true;
            body = r_body;
            body_content_type = r_content_type;
        }

        void request_info::set_body(const web::json::value& r_body)
        {
            set_body(r_body.serialize(), "application/json");
        }
    }
}
