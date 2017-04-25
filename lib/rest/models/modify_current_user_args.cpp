#include <disccord/rest/models/modify_current_user_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_current_user_args::modify_current_user_args()
            { }

            modify_current_user_args::~modify_current_user_args()
            { }

            void modify_current_user_args::encode_to(std::unordered_map<std::string, web::json::value>& info)
            {
                #define encode_field(var) \
                    if (var.is_specified()) \
                        info[#var] = web::json::value(var.get_value());

                encode_field(name);
                encode_field(avatar);

                #undef encode_field
            }

            #define define_set_method(field_name, type) \
                void modify_current_user_args::set_##field_name(type val) { \
                    field_name = decltype(field_name)(val); \
                }

            define_set_method(name, std::string)
            
            void modify_current_user_args::set_avatar(concurrency::streams::basic_istream<unsigned char> avatar_stream)
            {
                concurrency::streams::container_buffer<std::vector<unsigned char>> stream_buffer;
                avatar_stream.read_to_end(stream_buffer).get();
                auto stream_bytes = std::move(stream_buffer.collection());
                stream_buffer.close();
                std::string avatar_body = "data:image/jpeg;base64," + utility::conversions::to_base64(stream_bytes);
                avatar = util::optional<std::string>(avatar_body);
            }

            #undef define_set_method
        }
    }
}
