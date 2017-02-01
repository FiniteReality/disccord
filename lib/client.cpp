#include <client.hpp>

#include <rest.hpp>

namespace disccord
{
    Client::Client()
        : websocket(), rest_client()
    { }

    Client::~Client()
    { }
}