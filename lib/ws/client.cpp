#include <chrono>
#include <functional>

#include <disccord/rest.hpp>
#include <disccord/ws/client.hpp>

#include <disccord/util/task_sleep.hpp>

#include <disccord/models/ws/hello.hpp>

#include "dispatches.hpp"

using namespace std::chrono;

namespace disccord
{
namespace ws
{

static const web::uri base_uri(DISCORD_API_BASE_URL);

discord_ws_client::discord_ws_client(std::string token,
                                     disccord::token_type type)
    : rest_api_client(base_uri, token, type),
      ws_api_client(rest_api_client, token, type),
      heartbeat_cancel_token(), heartbeat_task(), seq(0)
{
    ws_api_client.set_frame_handler([this](
        const disccord::models::ws::frame * frame)
    {
        return this->handle_frame(frame);
    });
}

pplx::task<void> discord_ws_client::connect(
    const pplx::cancellation_token& token)
{
    return ws_api_client.connect(token);
}

void discord_ws_client::on_message(
    std::function<pplx::task<void>(disccord::models::message&)> handler)
{
    message_received = handler;
}

int64_t discord_ws_client::latency()
{
    return _latency;
}

pplx::task<void> discord_ws_client::handle_frame(
    const disccord::models::ws::frame* frame)
{
    if (frame->s.has_value())
    {
        uint32_t cur_seq = seq;
        uint32_t new_seq = frame->s;

        if (new_seq > cur_seq)
            if (!seq.compare_exchange_weak(cur_seq, new_seq))
                std::cout << "Failed to increment sequence:" <<
                          "Resuming may give bad data" << std::endl;
    }

    std::cout << "Got opcode "
              << static_cast<uint32_t>(frame->op)
              << std::endl;

    switch (frame->op)
    {
        case opcode::HELLO:
            {
                auto data = frame->get_data<models::ws::hello>();

                last_heartbeat_time = duration_cast<milliseconds>(
                    high_resolution_clock::now().time_since_epoch())
                    .count();

                auto func = std::bind(&discord_ws_client::heartbeat_loop,
                                      this, data.heartbeat_interval);
                heartbeat_task = pplx::create_task(func,
                    pplx::task_options(
                        heartbeat_cancel_token.get_token()));

                return ws_api_client.send_identify();
            }

        case opcode::HEARTBEAT:
            {
                return ws_api_client.send_heartbeat(seq);
            }

        case opcode::HEARTBEAT_ACK:
            {
                int64_t now = duration_cast<milliseconds>(
                    high_resolution_clock::now().time_since_epoch())
                    .count();

                _latency = now - last_heartbeat_time;
                last_heartbeat_time = now;
                break;
            }

        case opcode::DISPATCH:
            {
                std::string type = frame->t;
                auto* mapping =
                    Perfect_Hash::in_word_set(type.c_str(), type.size());

                if (mapping != nullptr)
                {
                    return handle_dispatch(frame, mapping->dispatch);
                }

                break;
            }

        default:
            std::cout << "Unhandled opcode " <<
                      static_cast<uint32_t>(frame->op) << std::endl;
    }

    return pplx::create_task([] {});
}

pplx::task<void> discord_ws_client::handle_dispatch(
    const disccord::models::ws::frame* frame,
    disccord::ws::dispatch dispatch)
{
    switch (dispatch)
    {
        case disccord::ws::dispatch::MESSAGE_CREATE:
        {
            auto message = frame->get_data<disccord::models::message>();
            return message_received(message);
        }
        default:
            std::cout << "Unhandled dispatch " <<
                static_cast<uint32_t>(dispatch) << std::endl;
    }

    return pplx::create_task([] {});
}

void discord_ws_client::heartbeat_loop(int wait_millis)
{
    while (!pplx::is_task_cancellation_requested())
    {
        int64_t now = duration_cast<milliseconds>(
            high_resolution_clock::now().time_since_epoch())
            .count();

        // TODO: this should probably notify the client rather than
        // throw
        if (now > last_heartbeat_time + wait_millis)
        {
            std::cout << "missed last heartbeat" << std::endl;
            throw std::runtime_error("Missed last heartbeat");
        }

        ws_api_client.send_heartbeat(seq).then([&]
        {
            return pplxtra::task::sleep(wait_millis);
        }).wait();
    }

    pplx::cancel_current_task();
}

}
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
