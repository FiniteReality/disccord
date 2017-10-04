#include <string>

#include <disccord/models/relationship.hpp>

namespace disccord
{
    namespace models
    {
        relationship::relationship()
            : entity(), user(), type()
        { }

        relationship::~relationship()
        { }

        void relationship::decode(web::json::value json)
        {
            entity::decode(json);

            switch(json.at("type").as_integer())
            {
                case uint32_t(relationship_type::Friend):
                    type = util::optional<uint32_t>(1);
                    break;
                case uint32_t(relationship_type::Blocked):
                    type = util::optional<uint32_t>(2);
                    break;
                case uint32_t(relationship_type::IncomingPending):
                    type = util::optional<uint32_t>(3);
                    break;
                case uint32_t(relationship_type::OutgoingPending):
                    type = util::optional<uint32_t>(4);
                    break;
                default:
                    type = util::optional<uint32_t>::no_value();
                    break;
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

            get_composite_field(user, models::user);

            #undef get_composite_field
        }

        void relationship::encode_to(
            std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            if (get_type().is_specified())
                info["type"] = web::json::value(get_type().get_value());
            if (get_user().is_specified())
                info["user"] = get_user().get_value().encode();
        }

        #define define_get_method(field_name) \
            decltype(relationship::field_name) \
                     relationship::get_##field_name() { \
                return field_name; \
            }

        define_get_method(type)
        define_get_method(user)

        #undef define_get_method
    }
}
