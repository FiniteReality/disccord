#include <iostream>

#include <disccord/disccord.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

#include <disccord/ws/models/gateway_model.hpp>

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

            ws_api_client::ws_api_client(const web::uri& base_uri, disccord::rest::internal::rest_api_client& rest_api, std::string acct_token, disccord::token_type type)
                : ws_client(), token(acct_token), token_type(type), rest_api_client(rest_api)
            {
                //setup_headers(ws_client);
                ws_client.set_message_handler([this](const websocket_incoming_message& msg)
                {
                    this->handle_message(msg);
                });
            }

            ws_api_client::ws_api_client(const web::uri& base_uri, disccord::rest::internal::rest_api_client& rest_api, std::string acct_token, disccord::token_type type, const websocket_client_config& client_config)
                : ws_client(client_config), token(acct_token), token_type(type), rest_api_client(rest_api)
            {
                //setup_headers(ws_client);
                ws_client.set_message_handler([this](const websocket_incoming_message& msg)
                {
                    this->handle_message(msg);
                });
            }

            ws_api_client::~ws_api_client()
            { }

            pplx::task<void> ws_api_client::connect(const pplx::cancellation_token &token)
            {
                return rest_api_client.get_gateway(token).then([this](disccord::models::gateway_info info)
                {
                    auto builder = web::uri_builder(web::uri(info.get_url()));
                    builder
                        .append_query("encoding", "etf") // TODO: should this be an option?
                        .append_query("v", DISCORD_GATEWAY_API_VERSION);
                    return ws_client.connect(builder.to_uri());
                });
            }

            void ws_api_client::handle_message(const websocket_incoming_message& message)
            {
                std::cout << "message received: " << (int)message.message_type() << " " << message.length() << " bytes" << std::endl;

                Concurrency::streams::istream body = message.body();

                auto buf = body.streambuf();
                const size_t size = buf.size();
                std::vector<unsigned char> buffer;
                buffer.reserve(size);
                auto range = boost::iterator_range<std::vector<unsigned char>::iterator>(buffer.begin(), buffer.end());

                switch (message.message_type())
                {
                    case websocket_message_type::binary_message:
                        buf.getn(buffer.data(), size).then([&range, size](size_t read)
                        {
                            assert(read == size); //TODO: better validation for this
                            return bert::parse(range);
                        }).then([](std::vector<bert::value> values)
                        {
                            for (auto& value : values)
                            {
                                std::cout << "ETF type: " << (int)value.get_type() << std::endl;
                            }

                            //disccord::ws::models::gateway_model model;
                            //model.decode(values.front());

                            //return model;
                        }).wait();
                        break;
                    case websocket_message_type::text_message:
                        break;
                    case websocket_message_type::close:
                        // TODO: handle closes
                        break;
                    case websocket_message_type::ping:
                    case websocket_message_type::pong:
                        // TODO: handle ping/pong
                        break;
                }
            }
        }
    }
}
