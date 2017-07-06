#ifndef _gateway_model_hpp_
#define _gateway_model_hpp_

#include <vector>

#include <bert.hpp>

#include <disccord/models/model.hpp>

namespace disccord
{
    namespace ws
    {
        namespace models
        {
            class gateway_model : public disccord::models::model
            {
                public:
                    gateway_model();
                    virtual ~gateway_model();

                    virtual void decode(bert::value etf);
                    bert::value encode_etf();

                protected:
                    virtual void encode_to(bert::value &etf);
            };
        }
    }
}

#endif /* _gateway_model_hpp_ */
