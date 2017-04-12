#include <string>

#include <disccord/models/guild_prune.hpp>

namespace disccord
{
    namespace models
    {
        guild_prune::guild_prune()
            : days(0)
        { }

        guild_prune::~guild_prune()
        { }

        void guild_prune::decode(web::json::value json)
        {
            days = json.at("days").as_integer();
        }

        void guild_prune::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["days"] = web::json::value(get_days());
        }

        #define define_get_method(field_name) \
            decltype(guild_prune::field_name) guild_prune::get_##field_name() { \
                return field_name; \
            }

        define_get_method(days)

        #undef define_get_method
    }
}
