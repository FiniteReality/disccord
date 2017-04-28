#include <disccord/rest/models/execute_webhook_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            execute_webhook_args::execute_webhook_args(std::string _content)
                : content(util::optional<std::string>(_content))
            { }

            execute_webhook_args::execute_webhook_args(std::vector<disccord::models::embed> _embeds)
                : embeds(util::optional<std::vector<disccord::models::embed>>(_embeds))
            { }

            execute_webhook_args::~execute_webhook_args()
            { }

            void execute_webhook_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(content);
                encode_field(username);
                encode_field(avatar_url);
                encode_field(tts);
                if (embeds.is_specified())
                {
                    auto _embeds = embeds.get_value();
                    std::vector<web::json::value> embed_array(_embeds.size());
                    std::transform(_embeds.begin(), _embeds.end(), embed_array.begin(), [](disccord::models::embed field)
                        {
                            return field.encode();
                        });
                    info["embeds"] = web::json::value::array(embed_array);
                }

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void execute_webhook_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(username, std::string)
            define_set_method(avatar_url, std::string)
            define_set_method(tts, bool)

            #undef define_set_method
        }
    }
}
