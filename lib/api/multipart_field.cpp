#include <disccord/api/multipart_field.hpp>

#include <stdexcept>

namespace disccord
{
    namespace api
    {
        multipart_field::multipart_field(std::string field_name, std::string type)
            : name(field_name), content_type(type)
        { }

        multipart_field::~multipart_field()
        { }

        std::string multipart_field::get_content_type()
        {
            return content_type;
        }

        std::string multipart_field::get_content()
        {
            throw new std::runtime_error("multipart_field::get_content() not overloaded!");
        }

        std::string multipart_field::get_name()
        {
            return name;
        }

        std::unordered_map<std::string, std::string> multipart_field::get_attributes()
        {
            std::unordered_map<std::string, std::string> attributes;

            attributes["name"] = get_name();

            return attributes;
        }
    }
}
