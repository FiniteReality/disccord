#include <string>

#include <disccord/models/relationship.hpp>

namespace disccord
{
    namespace models
    {
        relationship::relationship()
            : user(), type()
        { }

        relationship::~relationship()
        { }

        void relationship::decode(web::json::value json)
        {
            entity::decode(json);

            #define get_enum_field(var, type) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        auto val = type(field.as_integer()); \
                        var = decltype(var)(val); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            #define get_composite_field(var, type) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null()) { \
                        type val; \
                        val.decode(field); \
                        var = decltype(var)(val); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

            get_enum_field(type, relationship_type);
            get_composite_field(user, models::user);

            #undef get_enum_field
            #undef get_composite_field
        }

        void relationship::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            if (get_type().is_specified())
                info["type"] = web::json::value((uint8_t)get_type().get_value());
            if (get_user().is_specified())
                info["user"] = get_user().get_value().encode();
        }

        #define define_get_method(field_name) \
            decltype(relationship::field_name) relationship::get_##field_name() { \
                return field_name; \
            }

        define_get_method(type)
        define_get_method(user)

        #undef define_get_method
    }
}
