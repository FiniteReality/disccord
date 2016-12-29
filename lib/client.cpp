#include <client.hpp>

#include <rest.hpp>

namespace disccord
{
    Client::Client()
        : websocket(), rest_client(web::uri(DISCORD_BASE_URL))
    { }

    Client::~Client()
    { }

    void Connect(std::string token, TokenType tokenType)
    {
        // TODO: this
    }
}