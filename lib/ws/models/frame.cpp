#include <disccord/ws/models/frame.hpp>

#include <iostream>

namespace disccord
{
    namespace ws
    {
        namespace models
        {
            frame::frame()
                : opcode(0), data(), sequence(), event()
            { }

            frame::~frame()
            { }

            void frame::decode(web::json::value json)
            {
                if (json.has_field("op"))
                    opcode = json.at("op").as_integer();

                #define get_field(var, name, conv) \
                    if (json.has_field(name)) { \
                        auto field = json.at(name); \
                        if (!field.is_null()) { \
                            var = decltype(var)(field.conv()); \
                        } else { \
                            var = decltype(var)::no_value(); \
                        } \
                    } else { \
                        var = decltype(var)(); \
                    }

                get_field(sequence, "s", as_integer);
                get_field(event, "t", as_string);

                if (json.has_field("d"))
                    data = json.at("d");
                else
                    data = web::json::value::null();

                #undef get_field
            }

            void frame::encode_to(std::unordered_map<std::string, web::json::value> &info)
            {
                info["op"] = web::json::value::number(opcode);
                info["d"] = data;
                info["s"] = sequence;
                info["t"] = event;
            }

            int frame::get_opcode() const
            {
                return opcode;
            }
            util::optional<int> frame::get_sequence() const
            {
                return sequence;
            }
            util::optional<std::string> frame::get_event() const
            {
                return event;
            }
        }
    }
}
