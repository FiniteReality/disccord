#ifndef _game_hpp_
#define _game_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class game : public model
        {
            public:
                game();
                virtual ~game();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                util::optional<std::string> get_url();
                util::optional<uint8_t> get_type();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name;
                util::optional<std::string> url;
                util::optional<uint8_t> type; //should we have an enum for this?
        };
    }
}

#endif /* _game_hpp_ */
