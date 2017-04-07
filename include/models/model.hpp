#ifndef _model_hpp_
#define _model_hpp_

#include <json.h>

namespace disccord
{
    namespace models
    {
        class model
        {
            public:
                model();
                virtual ~model();

                virtual void decode(web::json::value json);
                web::json::value encode();
                web::json::value encode_array();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info);
                virtual void encode_to(std::vector<web::json::value> &info);
        };
    }
}

#endif /* _model_hpp_ */
