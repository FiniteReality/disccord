#ifndef _ws_client_hpp_
#define _ws_client_hpp_

#include <string>

#include <cpprest/ws_client.h>

#include <disccord/ws/event.hpp>
#include <disccord/token_type.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>
#include <disccord/ws/dispatcher.hpp>

namespace disccord
{

    namespace ws
    {
        class discord_ws_client
        {
            public:
                discord_ws_client(std::string token, disccord::token_type type);
                virtual ~discord_ws_client();

                pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());
                
                void event(event::event ev, std::function<void ()> func);

                template<typename LambdaType>
                void event(event::event ev, LambdaType lambda)
                {
                    dispatcher.on(ev, lambda);
                }

            private:
                disccord::rest::internal::rest_api_client rest_api_client;
                disccord::ws::internal::ws_api_client ws_api_client;
                
                disccord::ws::internal::dispatcher dispatcher;

                pplx::cancellation_token_source heartbeat_cancel_token;
                pplx::task<void> heartbeat_task;

                pplx::task<void> handle_frame(const disccord::ws::models::frame* frame);
                pplx::task<void> heartbeat_loop(int wait_millis);
        };
    }
}

#endif /* _ws_client_hpp_ */
