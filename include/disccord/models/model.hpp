#ifndef _model_hpp_
#define _model_hpp_

#include <string>
#include <unordered_map>

#include <cpprest/json.h>

namespace disccord
{
    namespace models
    {
        class model
        {
            public:
                model();
                virtual ~model();

                void decode_string(std::string info);

                virtual void decode(web::json::value json);
                web::json::value encode();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info);
        };
    }
}

#endif /* _model_hpp_ */
