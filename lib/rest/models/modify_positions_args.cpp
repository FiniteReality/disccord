#include <disccord/rest/models/modify_positions_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_positions_args::modify_positions_args(std::vector<std::pair<uint64_t, uint8_t>> _params)
            : id_pos_params(_params)
            { }

            modify_positions_args::~modify_positions_args()
            { }

            web::json::value modify_positions_args::encode()
            {
                auto _params = get_id_pos_params();
                std::vector<web::json::value> params_array(_params.size());
                std::transform(_params.begin(), _params.end(), params_array.begin(), [](std::pair<uint64_t, uint8_t> param)
                    {
                        web::json::value obj;
                        obj["id"] = web::json::value(param.first);
                        obj["position"] = web::json::value(param.second);
                        return obj;
                    });

                return web::json::value::array(params_array);
            }

            std::vector<std::pair<uint64_t, uint8_t>> modify_positions_args::get_id_pos_params()
            {
                return id_pos_params;
            }
        }
    }
}
