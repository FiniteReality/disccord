#ifndef _multipart_request_hpp_
#define _multipart_request_hpp_

#include <string>
#include <vector>

#include <disccord/api/multipart_field.hpp>

namespace disccord
{
    namespace api
    {
        class multipart_request
        {
            public:
                multipart_request(std::string content_type, std::string boundary = generate_boundary());
                virtual ~multipart_request();

                std::string encode();
                std::string get_content_type();

                void add_field(multipart_field field);

            private:
                static std::string generate_boundary();

                std::string content_type_suffix;
                std::string multipart_boundary;
                std::vector<multipart_field> fields;
        };
    }
}

#endif /* _multipart_request_hpp_ */
