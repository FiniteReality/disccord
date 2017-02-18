#include <models/entity.hpp>

#include <vector>
#include <cstdlib>
#include <iostream>

namespace disccord
{
    namespace models
    {
        entity::entity()
            : id(0)
        { }
        
        entity::~entity()
        { }

        void entity::decode(web::json::value json)
        {
            id = std::stoull(json.at("id").as_string());
        }

        web::json::value entity::encode()
        {
            std::unordered_map<std::string, web::json::value> info;
            encode_to(info);

            std::vector<std::pair<std::string, web::json::value>> fields(info.begin(), info.end());

            return web::json::value::object(fields);
        }

        void entity::encode_to(std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value::string(std::to_string(get_id()));
        }
        
        uint64_t entity::get_id()
        {
            return id;
        }
    }
}