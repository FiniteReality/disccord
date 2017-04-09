#include <models/model.hpp>

namespace disccord
{
    namespace models
    {
        model::model()
        { }

        model::~model()
        { }

        web::json::value model::encode()
        {
            std::unordered_map<std::string, web::json::value> info;
            encode_to(info);

            std::vector<std::pair<std::string, web::json::value>> fields(info.begin(), info.end());

            return web::json::value::object(fields);
        }

        void model::decode_string(std::string info)
        {
            decode(web::json::value::parse(info));
        }

        void model::decode(web::json::value json)
        { }

        void model::encode_to(std::unordered_map<std::string, web::json::value> &info)
        { }
    }
}
