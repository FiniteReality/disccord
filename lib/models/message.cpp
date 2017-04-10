#include <string>

#include <disccord/models/message.hpp>

namespace disccord
{
    namespace models
    {
        message::message()
            : entity(), author(), channel_id(0), content(""),
            timestamp(""), edited_timestamp(), nonce(),
            webhook_id(), tts(false), mention_everyone(false),
            pinned(false), mentions(), mention_roles(),
            attachments(), embeds(), reactions()
        { }

        message::~message()
        { }

        void message::decode(web::json::value json)
        {
            entity::decode(json);

            channel_id = std::stoull(json.at("channel_id").as_string());
            content = json.at("content").as_string();
            timestamp = json.at("timestamp").as_string();
            tts = json.at("tts").as_bool();
            mention_everyone = json.at("mention_everyone").as_bool();
            pinned = json.at("pinned").as_bool();

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

            get_field(edited_timestamp, as_string);
            get_field(nonce, as_string);
            get_field(webhook_id, as_string);

            get_composite_field(author, user);

            get_composite_field_vector(mentions, user);
            get_composite_field_vector(mention_roles, role);
            get_composite_field_vector(attachments, attachment);
            get_composite_field_vector(embeds, embed);
            get_composite_field_vector(reactions, reaction);

            #undef get_field
            #undef get_composite_field
            #undef get_composite_field_vector
        }

        void message::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            entity::encode_to(info);

            info["channel_id"] = web::json::value(std::to_string(get_channel_id()));
            info["content"] = web::json::value(get_content());
            info["timestamp"] = web::json::value(get_timestamp());
            info["tts"] = web::json::value(get_tts());
            info["mention_everyone"] = web::json::value(get_mention_everyone());
            info["pinned"] = web::json::value(get_pinned());

            if (edited_timestamp.is_specified())
                info["edited_timestamp"] = web::json::value(get_edited_timestamp().get_value());
            if (nonce.is_specified())
                info["nonce"] = web::json::value(get_nonce().get_value());
            if (webhook_id.is_specified())
                info["webhook_id"] = web::json::value(get_webhook_id().get_value());
            if (author.is_specified())
                info["author"] = get_author().get_value().encode();

            #define encode_composite_vector(var, type) \
                if (var.is_specified()) { \
                    auto _array = get_##var().get_value(); \
                    std::vector<web::json::value> array(_array.size()); \
                    std::transform(_array.begin(), _array.end(), array.begin(), \
                    [](type _field){ \
                        return _field.encode(); \
                    }); \
                    info[#var] = web::json::value::array(array); \
                } 

            encode_composite_vector(mentions, user);
            encode_composite_vector(mention_roles, role);
            encode_composite_vector(attachments, attachment);
            encode_composite_vector(embeds, embed);
            encode_composite_vector(reactions, reaction);

            #undef encode_composite_vector

        }


        #define define_get_method(field_name) \
            decltype(message::field_name) message::get_##field_name() { \
                return field_name; \
            }

        define_get_method(author)
        define_get_method(channel_id)
        define_get_method(content)
        define_get_method(timestamp)
        define_get_method(edited_timestamp)
        define_get_method(nonce)
        define_get_method(webhook_id)
        define_get_method(tts)
        define_get_method(mention_everyone)
        define_get_method(pinned)
        define_get_method(mentions)
        define_get_method(mention_roles)
        define_get_method(attachments)
        define_get_method(embeds)
        define_get_method(reactions)

        #undef define_get_method
    }
}
