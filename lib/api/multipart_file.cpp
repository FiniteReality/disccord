#include <api/multipart_file.hpp>

namespace disccord
{
    namespace api
    {
        multipart_file::multipart_file(std::string field_name, std::string file_name, std::string contents, std::string content_type)
            : multipart_field(field_name, content_type), filename(file_name), data(contents)
        { }

        multipart_file::~multipart_file()
        { }

        std::string multipart_file::get_file_name()
        {
            return filename;
        }

        std::string multipart_file::get_content()
        {
            return data;
        }

        std::unordered_map<std::string, std::string> multipart_file::get_attributes()
        {
            auto attrs = multipart_field::get_attributes();

            attrs["filename"] = get_file_name();

            return attrs;
        }
    }
}
