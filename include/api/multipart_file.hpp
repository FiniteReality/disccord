#ifndef _multipart_file_hpp_
#define _multipart_file_hpp_

#include <api/multipart_field.hpp>
#include <ostream>

namespace disccord
{
    namespace api
    {
        class multipart_file : public multipart_field
        {
            public:
                multipart_file(std::string field_name, std::string file_name, std::ostream content, std::string content_type);
                virtual ~multipart_file();

                virtual std::string get_content() override;

                virtual std::unordered_map<std::string, std::string> get_attributes() override;

            private:
                std::string filename;
                std::istream stream;
        };
    }
}

#endif /* _multipart_file_hpp_ */
