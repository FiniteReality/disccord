#include <rest/models/modify_guild_embed_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_embed_args::modify_guild_embed_args()
            { }

            modify_guild_embed_args::~modify_guild_embed_args()
            { }

            void modify_guild_embed_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {

                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(enabled);
                encode_field(channel_id);

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void modify_guild_embed_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(enabled, bool)
            define_set_method(channel_id, uint64_t)

            #undef define_set_method
        }
    }
}
