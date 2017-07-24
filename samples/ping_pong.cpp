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
        token_type = disccord::token_type::Bot;
    }
    else if (type == "user")
    {
        token_type = disccord::token_type::User;
    }
    else
    {
        std::cerr << "Unknown token type `" << type << "`" << std::endl;
        return EXIT_FAILURE;
    }

    discord_ws_client client {token, token_type};

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
