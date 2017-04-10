#include <chrono>

#include <disccord/api/multipart_request.hpp>

using namespace std::chrono;

namespace disccord
{
    namespace api
    {
        multipart_request::multipart_request(std::string content_type, std::string boundary)
            : content_type_suffix(content_type), multipart_boundary(boundary), fields()
        { }

        multipart_request::~multipart_request()
        { }

        std::string multipart_request::encode()
        {
            std::string body;
            for (auto& field : fields)
            {
                body += "--" + multipart_boundary + "\r\n";
                body += "Content-Disposition: " + content_type_suffix;
                for (auto& attribute_pair : field.get_attributes())
                {
                    // HACK: no encoding is done here! values may be unsanitary!
                    body += "; " + attribute_pair.first + "=\"" + attribute_pair.second + "\"";
                }
                body += "\r\nContent-Type: " + field.get_content_type() + "\r\n\r\n";
                body += field.get_content() + "\r\n";
            }
            body += "--";

            return body;
        }

        std::string multipart_request::get_content_type()
        {
            return "multipart/" + content_type_suffix;
        }

        void multipart_request::add_field(multipart_field field)
        {
            fields.push_back(field);
        }

        std::string multipart_request::generate_boundary()
        {
            auto current_time = high_resolution_clock::now().time_since_epoch();

            return "Upload----" + std::to_string(duration_cast<nanoseconds>(current_time).count());
        }
    }
}
