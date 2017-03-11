#ifndef _reaction_hpp_
#define _reaction_hpp_

#include <models/entity.hpp>
#include <models/emoji.hpp>

namespace disccord
{
    namespace models
    {
        class reaction : public model
        {
            public:
                reaction();
                virtual ~reaction();

                virtual void decode(web::json::value json) override;

                uint16_t get_count();
                bool get_me();
                util::optional<emoji> get_emoji_();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint16_t count;
                bool me;
                util::optional<emoji> emoji_;
        };
    }
}

#endif /* _reaction_hpp_ */
