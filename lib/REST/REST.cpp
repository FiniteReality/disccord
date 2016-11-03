#include <REST.hpp>

using http_response = web::http::http_response;
using json_value = web::json::value;

namespace disccord
{
    namespace REST
    {
        pplx::task<json_value> getGateway(discord_rest_client& client, std::string& encoding)
        {
            return client.request("GET", "/gateway").then([](http_response response){
                return response.extract_json();
            });
        }
    }
}