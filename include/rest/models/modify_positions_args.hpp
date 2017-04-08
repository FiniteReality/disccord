#ifndef _modify_positions_args_hpp_
#define _modify_positions_args_hpp_

#include <models/model.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_positions_args : public disccord::models::model
            {
                public:
                    modify_positions_args(std::vector<std::pair<uint64_t, uint8_t>> id_pos_params);
                    virtual ~modify_positions_args();

                    std::vector<std::pair<uint64_t, uint8_t>> get_id_pos_params();

                protected:
                    virtual void encode_to(std::vector<web::json::value>& info) override;

                private:
                    std::vector<std::pair<uint64_t, uint8_t>> id_pos_params;
            };
        }
    }
}

#endif /* _modify_positions_args_hpp_ */
