#include <iostream>

#include <cpprest/interopstream.h>

#include <disccord/disccord.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

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
                    auto builder = web::uri_builder(web::uri(info.get_url()));
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

            void ws_api_client::set_frame_handler(const std::function<pplx::task<void>(const disccord::ws::models::frame*)>& func)
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

                        models::frame* frame = new models::frame();
                        frame->decode(body);

                        models::frame const* frame_c = frame;
                        return message_handler(frame_c).then([frame]()
                        {
                            delete frame;
                        });
                    }
                    default:
                        std::cout << "unhandled ws message type: " << (int)message.message_type() << std::endl;
                }

                return pplx::create_task([](){});
            }
        }
    }
}
