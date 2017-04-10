#include <disccord/models/connection.hpp>

namespace disccord
{
    namespace models
    {
        connection::connection()
            : id(""), name(""), type(""),
            revoked(false), integrations()
        { }

        connection::~connection()
        { }

        void connection::decode(web::json::value json)
        {
            id = json.at("id").as_string();
            name = json.at("name").as_string();
            type = json.at("type").as_string();
            revoked = json.at("revoked").as_bool();

            #define get_composite_field_vector(var, type) \
                if (json.has_field(#var)) { \
                    auto _fields_array = json.at(#var).as_array(); \
                    std::vector<type> fields_array(_fields_array.size()); \
                    std::transform(_fields_array.begin(), _fields_array.end(), fields_array.begin(), \
                    [](web::json::value _field){ \
                        type field; \
                        field.decode(_field); \
                        return field; \
                    }); \
                    var = decltype(var)(fields_array); \
                } else { \
                    var = decltype(var)(); \
                }

            get_composite_field_vector(integrations, integration);

            #undef get_composite_field_vector
        }

        void connection::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
            info["type"] = web::json::value(type);
            info["revoked"] = web::json::value(revoked);
            if (integrations.is_specified())
            {
                auto _integrations = integrations.get_value();
                std::vector<web::json::value> field_array(_integrations.size());
                std::transform(_integrations.begin(), _integrations.end(), field_array.begin(), [](integration field)
                    {
                        return field.encode();
                    });
                info["integrations"] = web::json::value::array(field_array);
            }
        }

        #define define_get_method(field_name) \
            decltype(connection::field_name) connection::get_##field_name() { \
                return field_name; \
            }

        define_get_method(id)
        define_get_method(name)
        define_get_method(type)
        define_get_method(revoked)
        define_get_method(integrations)

        #undef define_get_method
    }
}
