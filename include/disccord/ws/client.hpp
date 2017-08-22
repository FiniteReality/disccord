#ifndef _ws_client_hpp_
#define _ws_client_hpp_

#include <atomic>
#include <string>

#include <cpprest/ws_client.h>

#include <disccord/types.hpp>
#include <disccord/rest/api_client.hpp>
#include <disccord/ws/api_client.hpp>

namespace disccord
{
    namespace ws
    {
        class discord_ws_client
        {
            public:
                // Define a custom ctor here as we need these values to operate
                discord_ws_client(std::string token,
                    disccord::token_type type);

                discord_ws_client(const discord_ws_client&) = delete;
                discord_ws_client& operator=(const discord_ws_client&)
                    = delete;
                // TODO: should we support move ctors here?
                discord_ws_client(discord_ws_client&&) = delete;
                discord_ws_client& operator=(discord_ws_client&&) = delete;

                // The default dtor can clean up our stuff easily
                ~discord_ws_client() = default;

                pplx::task<void> connect(const pplx::cancellation_token& token
                    = pplx::cancellation_token::none());

            private:
                disccord::rest::internal::rest_api_client rest_api_client;
                disccord::ws::internal::ws_api_client ws_api_client;

                pplx::cancellation_token_source heartbeat_cancel_token;
                pplx::task<void> heartbeat_task;

                // use atomics here because multiple frames can be sent at the
                // same time
                std::atomic<uint32_t> seq;
                std::atomic<int64_t> last_heartbeat_time;
                std::atomic<int64_t> latency;

                pplx::task<void> handle_frame(
                    const disccord::models::ws::frame* frame);
                void heartbeat_loop(int wait_millis);
        };
    }
}

#endif /* _ws_client_hpp_ */
