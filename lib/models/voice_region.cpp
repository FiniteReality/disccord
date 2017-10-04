#include <disccord/models/voice_region.hpp>

namespace disccord
{
    namespace models
    {
        voice_region::voice_region()
        : id(""), name(""), sample_hostname(),
        sample_port(), vip(false), optimal(false),
        deprecated(false), custom(false)
        { }

        voice_region::~voice_region()
        { }

        void voice_region::decode(web::json::value json)
        {
            id = json.at("id").as_string();
            name = json.at("name").as_string();
            vip = json.at("vip").as_bool();
            optimal = json.at("optimal").as_bool();
            deprecated = json.at("deprecated").as_bool();
            custom = json.at("custom").as_bool();

            #define get_field(var, conv) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        var = decltype(var)(field.conv()); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_field(sample_hostname, as_string);
            get_field(sample_port, as_integer);

            #undef get_field
        }

        void voice_region::encode_to(
            std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value(id);
            info["name"] = web::json::value(name);
            info["vip"] = web::json::value(vip);
            info["optimal"] = web::json::value(optimal);
            info["deprecated"] = web::json::value(deprecated);
            info["custom"] = web::json::value(custom);
            if (sample_hostname.is_specified())
                info["sample_hostname"] =
                    web::json::value(sample_hostname.get_value());
            if (sample_port.is_specified())
                info["sample_port"] =
                    web::json::value(sample_port.get_value());
        }

        #define define_get_method(field_name) \
            decltype(voice_region::field_name) \
                     voice_region::get_##field_name() { \
                return field_name; \
            }

        define_get_method(id)
        define_get_method(name)
        define_get_method(vip)
        define_get_method(optimal)
        define_get_method(deprecated)
        define_get_method(custom)
        define_get_method(sample_hostname)
        define_get_method(sample_port)

        #undef define_get_method
    }
}
