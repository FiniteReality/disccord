#ifndef _modify_positions_args_hpp_
#define _modify_positions_args_hpp_

#include <models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_positions_args
            {
                public:
                    modify_positions_args(std::vector<std::pair<uint64_t, uint8_t>> id_pos_params);
                    virtual ~modify_positions_args();

                    web::json::value encode();

                    std::vector<std::pair<uint64_t, uint8_t>> get_id_pos_params();

                private:
                    std::vector<std::pair<uint64_t, uint8_t>> id_pos_params;
            };
        }
    }
}

#endif /* _modify_positions_args_hpp_ */
