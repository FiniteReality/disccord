#include <string>

#include <disccord/models/nickname.hpp>

namespace disccord
{
    namespace models
    {
        nickname::nickname()
            : nick("")
        { }

        nickname::~nickname()
        { }

        void nickname::decode(web::json::value json)
        {
            nick = json.at("nick").as_string();
        }

        void nickname::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["nick"] = web::json::value(get_nick());
        }

        #define define_get_method(field_name) \
            decltype(nickname::field_name) nickname::get_##field_name() { \
                return field_name; \
            }

        define_get_method(nick)

        #undef define_get_method
    }
}
