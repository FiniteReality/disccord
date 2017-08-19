#include <functional>

#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

#include <disccord/util/task_sleep.hpp>

#include <disccord/models/ws/hello.hpp>

namespace disccord
{
    namespace ws
    {
        static const web::uri base_uri(DISCORD_API_BASE_URL);

        discord_ws_client::discord_ws_client(std::string token, disccord::token_type type, uint16_t shard_id, uint16_t shard_count)
            : rest_api_client(base_uri, token, type), ws_api_client(rest_api_client, token, type),
            heartbeat_cancel_token(), heartbeat_task(), heartbeat_times(), last_message_time(),
            seq(0), session_id(""), shard_id(shard_id), shard_count(shard_count), latency(0)
        {
            ws_api_client.set_frame_handler([this](const disccord::models::ws::frame* frame)
            {
                return this->handle_frame(frame);
            });
        }

        discord_ws_client::~discord_ws_client()
        { }

        pplx::task<void> discord_ws_client::connect(const pplx::cancellation_token& token)
        {
            return ws_api_client.connect(token);
        }

        uint32_t discord_ws_client::get_latency() const
        {
            return latency;
        }

        uint32_t discord_ws_client::get_shard_id() const
        {
            return shard_id;
        }

        pplx::task<void> discord_ws_client::handle_frame(const disccord::models::ws::frame* frame)
        {
            if (frame->s.is_specified())
                seq = frame->s.get_value();
            
            last_message_time = std::chrono::high_resolution_clock::now();

            // TODO: log the opcodes
            switch (frame->op)
            {
                case opcode::HELLO:
                {
                    auto data = frame->get_data<models::ws::hello>();

                    auto func = std::bind(&discord_ws_client::heartbeat_loop, this, data.heartbeat_interval);
                    heartbeat_task = pplx::create_task(func, pplx::task_options(heartbeat_cancel_token.get_token()));
                    
                    ws_api_client.send_identify(shard_id, shard_count).wait();

                    break;
                }
                case opcode::HEARTBEAT:
                {
                    ws_api_client.send_heartbeat(seq).wait();
                    break;
                }
                case opcode::HEARTBEAT_ACK:
                {
                    if (!heartbeat_times.empty())
                    {
                        auto time = heartbeat_times.front();
                        auto time_now = std::chrono::high_resolution_clock::now();
                        heartbeat_times.pop();

                        std::chrono::duration<double, std::milli> time_diff = time_now - time;
                        auto current_latency = static_cast<uint64_t>(time_diff.count());
                        //auto previous_latency = latency;
                        latency = current_latency;

                        // TODO: log previous vs current latency
                    }
                    break;
                }
                case opcode::INVALIDATE_SESSION:
                {
                    seq = 0;
                    session_id = "";

                    if (frame->d.as_bool())
                    {
                       // TODO: Reconnect here 
                    }
                    else 
                    {
                       ws_api_client.send_identify(shard_id, shard_count).wait(); 
                    }
                    break;
                }
                case opcode::RECONNECT:
                {
                    // TODO: Reconnect here
                    break;
                }
                case opcode::DISPATCH:
                {
                    handle_dispatch(frame);
                    break;
                }
                default:
                    std::cout << "Unhandled opcode " << static_cast<uint32_t>(frame->op) << std::endl;
            }

            return pplx::create_task([](){});
        }

        pplx::task<void> discord_ws_client::heartbeat_loop(int wait_ms)
        {
            return pplx::create_task([wait_ms, this](){
                while(!pplx::is_task_cancellation_requested())
                {
                    // TODO: error/exception checks

                    auto time_now = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> heartbeat_delay = time_now - last_message_time;

                    auto interval = static_cast<uint64_t>(wait_ms);
                    auto delay = static_cast<uint64_t>(heartbeat_delay.count());
                    
                    // check if our last heartbeat was responded to
                    if (!heartbeat_times.empty() && delay > interval)
                    {
                        // TODO: check if we are also still receiving messages (e.g. GUILD_CREATE)
                    }

                    heartbeat_times.push(time_now);

                    ws_api_client.send_heartbeat(seq).wait();

                    auto s = static_cast<double>(wait_ms)/1000;
                    util::task_sleep(s).wait();
                }

                pplx::cancel_current_task();
            });
        }
        
        void discord_ws_client::handle_dispatch(const disccord::models::ws::frame* frame)
        {
            // TODO: handle events
        }
    }
}
