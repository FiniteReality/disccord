#include <disccord/models/audit_log_change.hpp>

namespace disccord
{
    namespace models
    {
        // roles_change
        roles_change::roles_change()
            : name("")
        { }
        
        roles_change::~roles_change()
        { }
        
        void roles_change::decode(web::json::value json)
        {
            entity::decode(json);
            
            name = json.at("name").as_string();
        }
        
        void roles_change::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);
            
            info["name"] = web::json::value(name);
        }
        
        std::string roles_change::get_name()
        {
            return name;
        }
        
        // audit_log_change
        audit_log_change::audit_log_change()
            : key(""), new_value(), old_value()
        { }

        audit_log_change::~audit_log_change()
        { }

        void audit_log_change::decode(web::json::value json)
        {
            key = json.at("key").as_string();

            #define get_field(var) \
                if (json.has_field(#var)) { \
                    auto field = json.at(#var); \
                    if (!field.is_null() && !field.is_array() && !field.is_object()) { \
                        if (json.at(#var).is_number()) \
                            var = decltype(var)(std::to_string(json.at(#var).as_integer())); \
                        else if (json.at(#var).is_boolean()) \
                            var = decltype(var)(json.at(#var).as_bool()); \
                        else \
                            var = decltype(var)(json.at(#var).as_string()); \
                    } else { \
                        var = decltype(var)::no_value(); \
                    } \
                } else { \
                    var = decltype(var)(); \
                }

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
            
            if (key == "$add" || key == "$remove")
            {
                get_composite_field_vector(new_value, roles_change);
                get_composite_field_vector(old_value, roles_change);
            }
            else
            {
                get_field(new_value);
                get_field(old_value);
            }

            #undef get_field
            #undef get_composite_field_vector
        }

        void audit_log_change::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["key"] = web::json::value(key);
            
            #define encode_field(var) \
                if (var.is_specified()) { \
                    auto val = get_##var().get_value(); \
                    if (val.which() == 0) \
                        info[#var] = web::json::value(boost::get<uint64_t>(val)); \
                    else if (val.which() == 1) \
                        info[#var] = web::json::value(boost::get<std::string>(val)); \
                    else if (val.which() == 2) \
                        info[#var] = web::json::value(boost::get<bool>(val)); \
                } 
            
            #define encode_composite_vector(var, type) \
                if (var.is_specified()) { \
                    auto val = get_##var().get_value(); \
                    auto _array = boost::get<type>(val); \
                    std::vector<web::json::value> array(_array.size()); \
                    std::transform(_array.begin(), _array.end(), array.begin(), \
                    [](roles_change _field){ \
                        return _field.encode(); \
                    }); \
                    info[#var] = web::json::value::array(array); \
                }
            if (key == "$add" || key == "$remove")
            {
                encode_composite_vector(old_value, std::vector<roles_change>);
                encode_composite_vector(new_value, std::vector<roles_change>);
            }
            else
            {
                encode_field(new_value);
                encode_field(old_value);
            }
            
            #undef encode_field
            #undef encode_composite_vector
        }

        #define define_get_method(field_name) \
            decltype(audit_log_change::field_name) audit_log_change::get_##field_name() { \
                return field_name; \
            }

        define_get_method(key)
        define_get_method(new_value)
        define_get_method(old_value)

        #undef define_get_method
    }
}
