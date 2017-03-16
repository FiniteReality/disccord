#ifndef _ban_hpp_
#define _ban_hpp_

#include <models/entity.hpp>
#include <models/user.hpp>

namespace disccord
{
    namespace models
    {
        class ban : public model
        {
            public:
                ban();
                virtual ~ban();

                virtual void decode(web::json::value json) override;

                std::string get_reason();
                util::optional<models::user> get_user();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string reason;
                util::optional<models::user> user;
        };
    }
}

#endif /* _ban_hpp_ */
