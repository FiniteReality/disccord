#include <client.hpp>

#include <REST.hpp>

namespace disccord
{
    Client::Client()
        : websocket(), rest_client(web::uri(DISCORD_BASE_URL))
    { }

    void Connect(std::string token, TokenType tokenType)
    {
        // TODO: this
    }
}