#include <boost/lexical_cast.hpp>

#include <models/application.hpp>

namespace disccord
{
    namespace models
    {
        application::application()
        : id(), name(""), icon(), description(),
        rpc_origins(), bot_public(false),
        bot_requires_code_grant(false), owner()
        { }

        application::~application()
        { }

        void application::decode(web::json::value json)
        {
            id = boost::lexical_cast<uint64_t>(json.at("id").as_string());
            name = json.at("name").as_string();
            bot_public = json.at("bot_public").as_bool();
            bot_requires_code_grant = json.at("bot_requires_code_grant").as_bool();

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
            #define get_field_vector(var, type, conv) \
                if (json.has_field(#var)) { \
                    auto _fields_array = json.at(#var).as_array(); \
                    std::vector<type> fields_array(_fields_array.size()); \
                    std::transform(_fields_array.begin(), _fields_array.end(), fields_array.begin(), \
                    [&json](web::json::value _field){ \
                        type field; \
                        field = _field.conv(); \
                        return field; \
                    }); \
                    var = decltype(var)(fields_array); \
                } else { \
                    var = decltype(var)(); \
                }
                
            get_field(icon, as_string);
            get_field(description, as_string);
            get_composite_field(owner, user);
            get_field_vector(rpc_origins, std::string, as_string);
            
            #undef get_field
            #undef get_composite_field
            #undef get_field_vector
        }

        void application::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["name"] = web::json::value(name);
            info["id"] = web::json::value(id);
            info["bot_public"] = web::json::value(bot_public);
            info["bot_requires_code_grant"] = web::json::value(bot_requires_code_grant);
            
            if (icon.is_specified())
                info["icon"] = web::json::value(icon.get_value());
            if (description.is_specified())
                info["description"] = web::json::value(description.get_value());
            if (owner.is_specified())
                info["owner"] = owner.get_value().encode();
            if (rpc_origins.is_specified())
            {
                auto _rpc_origins = rpc_origins.get_value();
                std::vector<web::json::value> field_array(_rpc_origins.size());
                std::transform(_rpc_origins.begin(), _rpc_origins.end(), field_array.begin(),
                    [](std::string field){
                        return web::json::value(field);
                    });
                info["rpc_origins"] = web::json::value::array(field_array);
            }
        }
        
        #define define_get_method(field_name) \
            decltype(application::field_name) application::get_##field_name() { \
                return field_name; \
            }
        define_get_method(name);
        define_get_method(id);
        define_get_method(bot_public);
        define_get_method(bot_requires_code_grant);
        define_get_method(icon);
        define_get_method(description);
        define_get_method(owner);
        define_get_method(rpc_origins);
        
        #undef define_get_method
    }
}
