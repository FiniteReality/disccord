#include <iterator>

#include <REST.hpp>

using http_response = web::http::http_response;

namespace disccord
{
    namespace REST
    {
        pplx::task<std::string> getGateway(discord_rest_client& client, std::string& encoding)
        {
            return client.request("GET", "/gateway").then([](http_response response){
                return response.extract_json();
            }).then([](web::json::value json){
                web::json::object::const_iterator request_url = json.as_object().find("url");

                return std::get<1>((*request_url)).as_string();
            });
        }
    }
}