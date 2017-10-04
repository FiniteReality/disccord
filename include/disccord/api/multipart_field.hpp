#ifndef _multipart_field_hpp_
#define _multipart_field_hpp_

#include <string>
#include <unordered_map>

namespace disccord
{
    namespace api
    {
        class multipart_field
        {
            public:
                multipart_field(std::string field_name,
                                std::string content_type);
                virtual ~multipart_field();

                std::string get_content_type();
                virtual std::string get_content();

                virtual std::unordered_map<std::string,
                        std::string> get_attributes();

            private:
                std::string get_name();

                std::string name;
                std::string content_type;
        };
    }
}

#endif /* _multipart_field_hpp_ */
