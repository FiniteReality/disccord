#ifndef _embed_field_hpp_
#define _embed_field_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_field : public entity
        {
            public:
                embed_field();
                virtual ~embed_field();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                std::string get_value();
                util::optional<bool> get_inline();;

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name, value;
                util::optional<bool> _inline; //inline is keyword
        };
    }
}

#endif /* _embed_field_hpp_ */
