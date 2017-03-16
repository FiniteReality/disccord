#include <boost/lexical_cast.hpp>

#include <models/relationship.hpp>

namespace disccord
{
    namespace models
    {
        relationship::relationship()
            : id(0), user(), type()
        { }

        relationship::~relationship()
        { }

        void relationship::decode(web::json::value json)
        {
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
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

        void relationship::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value(id);
            if (type.is_specified())
                info["type"] = web::json::value(type.get_value());
            if (user.is_specified())
                info["user"] = user.get_value().encode();
        }
        
        #define define_get_method(field_name) \
            decltype(relationship::field_name) relationship::get_##field_name() { \
                return field_name; \
            }
        define_get_method(id);
        define_get_method(type);
        define_get_method(user);
        
        #undef define_get_method
    }
}
