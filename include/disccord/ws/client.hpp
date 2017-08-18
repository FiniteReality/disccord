#ifndef _ws_client_hpp_
#define _ws_client_hpp_

#include <string>
#include <queue>
#include <chrono>

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
                discord_ws_client(std::string token, disccord::token_type type, uint16_t shard_id = 0, uint16_t shard_count = 1);
                virtual ~discord_ws_client();

                pplx::task<void> connect(const pplx::cancellation_token& token = pplx::cancellation_token::none());
                
                uint32_t get_latency() const;
                uint32_t get_shard_id() const;

            private:
                using time = std::chrono::time_point<std::chrono::high_resolution_clock>;

                disccord::rest::internal::rest_api_client rest_api_client;
                disccord::ws::internal::ws_api_client ws_api_client;

                pplx::cancellation_token_source heartbeat_cancel_token;
                pplx::task<void> heartbeat_task;

                std::queue<time> heartbeat_times;
                time last_message_time;

                uint32_t seq;
                std::string session_id;

                uint16_t shard_id;
                uint16_t shard_count;
                uint32_t latency;

                pplx::task<void> handle_frame(const disccord::models::ws::frame* frame);
                pplx::task<void> heartbeat_loop(int wait_ms);
                
                pplx::task<void> handle_dispatch(const disccord::models::ws::frame* frame);
        };
    }
}

#endif /* _ws_client_hpp_ */
