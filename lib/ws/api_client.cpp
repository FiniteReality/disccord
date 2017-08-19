#include <iostream>
#include <memory>

#include <cpprest/interopstream.h>

#include <disccord/disccord.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

#include <disccord/models/ws/identify_args.hpp>
#include <disccord/models/ws/resume_args.hpp>
#include <disccord/models/ws/status_update_args.hpp>

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
                : ws_client(), token(acct_token), token_type(type), rest_api_client(rest_api), message_handler(), read_task(), cancel_token()
            { }

            ws_api_client::ws_api_client(disccord::rest::internal::rest_api_client& rest_api, std::string acct_token, disccord::token_type type, const websocket_client_config& client_config)
                : ws_client(client_config), token(acct_token), token_type(type), rest_api_client(rest_api), message_handler(), read_task(), cancel_token()
            { }

            ws_api_client::~ws_api_client()
            { }

            pplx::task<void> ws_api_client::connect(const pplx::cancellation_token &token)
            {
                return rest_api_client.get_gateway(token).then([this](disccord::models::gateway_info info)
                {
                    auto builder = web::uri_builder(web::uri(info.url));
                    builder
                        .append_query("encoding", "json") // TODO: ETF support
                        .append_query("v", DISCORD_GATEWAY_API_VERSION);
                    return ws_client.connect(builder.to_uri());
                }).then([this]()
                {
                    auto func = std::bind(&ws_api_client::read_loop, this);
                    read_task = pplx::create_task(func, pplx::task_options(cancel_token.get_token()));
                });
            }

            pplx::task<void> ws_api_client::send(ws::opcode op, web::json::value payload)
            {
                payload["op"] = web::json::value(static_cast<int>(op));
                websocket_outgoing_message gateway_msg;
                gateway_msg.set_utf8_message(std::move(payload.serialize()));
                return ws_client.send(gateway_msg);
            }

            void ws_api_client::set_frame_handler(const std::function<pplx::task<void>(const disccord::models::ws::frame*)>& func)
            {
                message_handler = func;
            }

            void ws_api_client::read_loop()
            {
                while(!pplx::is_task_cancellation_requested())
                {
                    ws_client.receive().then([this](const websocket_incoming_message& msg)
                    {
                        return this->handle_message(msg);
                    }).wait();
                }

                pplx::cancel_current_task();
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

                        std::unique_ptr<disccord::models::ws::frame> frame = std::make_unique<disccord::models::ws::frame>();
                        frame->decode(body);

                        disccord::models::ws::frame const* frame_c = frame.get();
                        return message_handler(frame_c).then([&frame]()
                        { });
                    }
                    default:
                        std::cout << "unhandled ws message type: " << (int)message.message_type() << std::endl;
                }

                return pplx::create_task([](){});
            }
            
            pplx::task<void> ws_api_client::send_heartbeat(const uint32_t sequence)
            {
                web::json::value payload;
                if (!sequence)
                    payload["d"] = web::json::value::null();
                else
                    payload["d"] = web::json::value(sequence);
                return send(ws::opcode::HEARTBEAT, payload);
            }
            
            pplx::task<void> ws_api_client::send_identify(const uint16_t shard_id, const uint16_t shard_count, const bool compress, const uint16_t large_threshold)
            {
                std::vector<web::json::value> shard_array = {web::json::value(shard_id), web::json::value(shard_count)};
                
                models::ws::identify_args args{token, compress, large_threshold, shard_array};
                
                web::json::value payload;
                payload["d"] = args.encode();
                payload["d"]["properties"]["$os"] = web::json::value("linux");
                payload["d"]["properties"]["$device"] = web::json::value("disccord");
                
                return send(ws::opcode::IDENTIFY, payload);
            }
            
            pplx::task<void> ws_api_client::send_resume(const std::string& session_id, const uint32_t sequence)
            {
                models::ws::resume_args args{token, session_id, sequence};
                
                web::json::value payload;
                payload["d"] = args.encode();
                
                return send(ws::opcode::RESUME, payload);
            }
            
            pplx::task<void> ws_api_client::send_status_update(const std::string& status, models::game game, bool afk, uint64_t since)
            {
                models::ws::status_update_args args{status, game, afk, since};
                
                web::json::value payload;
                payload["d"] = args.encode();
                
                // models generator doesnt support sending a field as null atm (based on a check), so this is temporary
                if (!since)
                    payload["d"]["since"] = web::json::value::null();
                
                return send(ws::opcode::PRESENCE, payload);
            }
        }
    }
}
