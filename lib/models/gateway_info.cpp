#include <disccord/models/gateway_info.hpp>

namespace disccord
{
    namespace models
    {
        gateway_info::gateway_info()
        { }
        gateway_info::~gateway_info()
        { }

        void gateway_info::decode(web::json::value json)
        {
            url = json.at("url").as_string();

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

            get_field(shards, as_integer);

            #undef get_field
        }

        std::string gateway_info::get_url() {
            return url;
        }

        util::optional<int> gateway_info::get_shards() {
            return shards;
        }
    }
}
