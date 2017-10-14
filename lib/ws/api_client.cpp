#include <iostream>
#include <memory>

#include <cpprest/interopstream.h>

#include <disccord/disccord.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

#include <disccord/models/ws/identify.hpp>

// This is purely for my sanity. Don't ever do this, ever.
using namespace web::websockets::client;

namespace disccord
{
    namespace ws
    {
        namespace internal
        {
            static inline void setup_headers(websocket_callback_client& client)
            {
                //TODO: figure out a way to do this
                //websocket_client_config& config = client.config();
                //web::http::http_headers& headers = config.headers();
                //headers.add("User-Agent", DISCORD_USER_AGENT);
            }

            ws_api_client::ws_api_client(disccord::rest::internal::rest_api_client& rest_api, std::string acct_token, disccord::token_type type)
                : ws_client(), token(acct_token), token_type(type), rest_api_client(rest_api), message_handler(), cancel_token()
            {
                ws_client.set_message_handler([&](auto& msg)
                {
                    handle_message(msg).wait();
                });
                ws_client.set_close_handler([&](auto status, auto& reason, auto& code)
                {
                    std::cout << "DISC: " << (short)status << " (" << reason << ") (" << code << ")" << std::endl;
                });
            }

            ws_api_client::ws_api_client(disccord::rest::internal::rest_api_client& rest_api, std::string acct_token, disccord::token_type type, const websocket_client_config& client_config)
                : ws_client(client_config), token(acct_token), token_type(type), rest_api_client(rest_api), message_handler(), cancel_token()
            {
                ws_client.set_message_handler([&](auto& msg)
                {
                    handle_message(msg).wait();
                });
                ws_client.set_close_handler([&](auto status, auto& reason, auto& code)
                {
                    std::cout << "DISC: " << (short)status << " (" << reason << ") (" << code << ")" << std::endl;
                });
            }

            ws_api_client::~ws_api_client()
            { }

            pplx::task<void> ws_api_client::connect(const pplx::cancellation_token &token)
            {
                return rest_api_client.get_gateway(token).then([&](disccord::models::gateway_info info)
                {
                    auto builder = web::uri_builder(web::uri(info.url));
                    builder
                        .append_query("encoding", "json") // TODO: ETF support
                        .append_query("v", DISCORD_GATEWAY_API_VERSION);
                    return ws_client.connect(builder.to_uri());
                });
            }

            pplx::task<void> ws_api_client::send(const disccord::models::ws::frame& frame)
            {
                websocket_outgoing_message message;
                web::json::value json = frame.encode();
                message.set_utf8_message(json.serialize());

                std::cout << "SEND: " << json.serialize() << std::endl;

                return ws_client.send(message);
            }

            pplx::task<void> ws_api_client::send(disccord::models::ws::frame&& frame)
            {
                websocket_outgoing_message message;
                web::json::value json = frame.encode();
                message.set_utf8_message(json.serialize());

                std::cout << "SEND: " << json.serialize() << std::endl;

                return ws_client.send(message);
            }

            void ws_api_client::set_frame_handler(const std::function<pplx::task<void>(const disccord::models::ws::frame*)>& func)
            {
                message_handler = func;
            }

            pplx::task<void> ws_api_client::handle_message(const websocket_incoming_message& message)
            {
                switch (message.message_type())
                {
                    case websocket_message_type::binary_message:
                    {
                        // TODO: compressed packet/ETF support
                        break;
                    }
                    case websocket_message_type::text_message:
                    {
                        auto raw_stream = message.body();
                        Concurrency::streams::async_istream<char> body_stream{raw_stream};

                        web::json::value body = web::json::value::parse(body_stream);

                        std::cout << "RECV: " << body.serialize() << std::endl;

                        auto frame = std::make_unique<disccord::models::ws::frame>();
                        frame->decode(body);

                        disccord::models::ws::frame const* frame_c = frame.get();
                        return message_handler(frame_c);
                    }
                    default:
                        std::cout << "unhandled ws message type: " << (int)message.message_type() << std::endl;
                }

                return pplx::create_task([](){});
            }

            pplx::task<void> ws_api_client::send_heartbeat(uint32_t sequence)
            {
                disccord::models::ws::frame frame;
                frame.op = disccord::ws::opcode::HEARTBEAT;
                frame.s = sequence;

                return send(frame);
            }

            pplx::task<void> ws_api_client::send_identify()
            {
                disccord::models::ws::frame frame;
                frame.op = disccord::ws::opcode::IDENTIFY;

                disccord::models::ws::identify payload
                {
                    token,
                    web::json::value::object(),
                    false,
                    250,
                    {0, 1}
                };

                frame.set_data(payload);

                return send(frame);
            }
        }
    }
}