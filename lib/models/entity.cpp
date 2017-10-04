#include <string>
#include <vector>

#include <disccord/models/entity.hpp>

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

        void entity::encode_to(
            std::unordered_map<std::string, web::json::value> &info)
        {
            info["id"] = web::json::value::string(std::to_string(get_id()));
        }

        uint64_t entity::get_id()
        {
            return id;
        }
    }
}
