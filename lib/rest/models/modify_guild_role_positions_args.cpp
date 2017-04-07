#include <rest/models/modify_positions_args.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            modify_guild_role_positions_args::modify_guild_role_positions_args(std::vector<std::pair<uint64_t, uint8_t>> _params)
            : id_pos_params(_params)
            { }
            
            modify_guild_role_positions_args::~modify_guild_role_positions_args()
            { }

            void modify_guild_role_positions_args::encode_to(std::vector<web::json::value>& info)
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
                info = params_array;
            }

            std::vector<std::pair<uint64_t, uint8_t>> modify_guild_role_positions_args::get_id_pos_params()
            {
                return id_pos_params;
            }
        }
    }
}
