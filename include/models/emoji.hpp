#ifndef _emoji_hpp_
#define _emoji_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class emoji : public model
        {
            public:
                emoji();
                virtual ~emoji();

                virtual void decode(web::json::value json) override;

                util::optional<uint64_t> get_id();
                std::string get_name();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name;
                util::optional<uint64_t> id;
        };
    }
}

#endif /* _emoji_hpp_ */
