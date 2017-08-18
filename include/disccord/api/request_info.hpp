#ifndef _request_info_hpp_
#define _request_info_hpp_

#include <unordered_map>

#include <cpprest/base_uri.h>
#include <cpprest/json.h>

namespace disccord
{
    namespace api
    {
        class request_info
        {
            public:
                request_info();
                request_info(const std::string& method, const web::uri& url);
                virtual ~request_info();

                std::string get_method() const;
                web::uri get_url() const;
                std::unordered_map<std::string, std::string> get_headers() const;
                bool get_has_body() const;
                std::string get_body() const;
                std::string get_content_type() const;

                void set_method(const std::string& method);
                void set_url(const web::uri& new_url);
                void set_header(const std::string& header, const std::string& value);
                void set_body(const std::string& body, const std::string& content_type);

                void set_body(const web::json::value& body);

            private:
                std::string method;
                web::uri url;
                std::unordered_map<std::string, std::string> headers;
                bool has_body;
                std::string body, body_content_type;
        };
    }
}

#endif /* _request_info_hpp_ */
