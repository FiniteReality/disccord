#include <iostream>
#include <string>
#include <cstdlib>

#include <cpprest/interopstream.h>

#include <disccord/ws/client.hpp>

using namespace disccord::ws;

std::string environment_variable(std::string name)
{
    if (const char* contents = std::getenv(name.c_str()))
    {
        return std::string(contents);
    }
    else
    {
        return "";
    }
}


int main()
{
    std::string token = environment_variable("BOT_TOKEN");
    std::string type = environment_variable("TOKEN_TYPE");

    if (token.empty())
    {
        std::cerr << "ERROR: Could not find a token in the `BOT_TOKEN` environment variable." << std::endl;
        return EXIT_FAILURE;
    }

    disccord::token_type token_type;

    if (type.empty() || type == "bot")
    {
        token_type = disccord::token_type::BOT;
    }
    else if (type == "user")
    {
        token_type = disccord::token_type::USER;
    }
    else
    {
        std::cerr << "Unknown token type `" << type << "`" << std::endl;
        return EXIT_FAILURE;
    }

    discord_ws_client client {token, token_type};

    client.on_message([&](disccord::models::message& message)
    {
        disccord::snowflake author_id;
        std::string author;
        if (message.author.has_value())
        {
            disccord::models::user user = message.author;
            author = user.username + "#" + std::to_string(user.discriminator);
            author_id = user.id;
        }
        else if (message.webhook_id.has_value())
        {
            author = "Webhook " + std::to_string(message.webhook_id);
        }

        if (message.content.has_value())
        {
            std::string content = message.content;
            std::cout << "Message from '" << author
                << "': " << content << std::endl;

            if (content.find("!ping") == 0)
            {
                if (author_id > 0)
                {
                    std::string contents =
                        "Hi, <@" + std::to_string(author_id) + ">! " +
                        "Ping: " + std::to_string(client.latency()) + "ms";
                    return client.rest_api_client.create_message(
                        message.channel_id,
                        disccord::models::rest::create_message_args{contents}
                    ).then([&](pplx::task<disccord::models::message> tsk){
                        try
                        {
                            tsk.get();
                        }
                        catch (std::exception e)
                        {
                            std::cout << "Exception occured: "
                                << e.what() << std::endl;
                        }
                    });
                }
            }
        }

        return pplx::create_task([] {});
    });

    std::cout << "Connecting..." << std::endl;

    client.connect().then([]()
    {
        std::cout << "Connected. Press any key to exit." << std::endl;
    }).wait();

    pplx::task_completion_event<void> event;

    Concurrency::streams::stdio_istream<std::istream::char_type> cin{std::cin};
    cin.read().then([&event](Concurrency::streams::stdio_istream<std::istream::char_type>::int_type c)
    {
        event.set();
    });

    pplx::create_task(event).wait();
}
