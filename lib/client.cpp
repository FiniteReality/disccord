#include <disccord/client.hpp>

#include <disccord/rest.hpp>

namespace disccord
{
    Client::Client()
        : websocket(), rest_client()
    { }

    Client::~Client()
    { }
}
