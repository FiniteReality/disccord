#ifndef _relationship_hpp_
#define _relationship_hpp_

#include <models/entity.hpp>
#include <models/user.hpp>
#include <models/relationship_type.hpp>

namespace disccord
{
    namespace models
    {
        class relationship : public model
        {
            public:
                relationship();
                virtual ~relationship();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                util::optional<models::user> get_user();
                util::optional<uint32_t> get_type();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
                util::optional<models::user> user;
                util::optional<uint32_t> type;
        };
    }
}

#endif /* _relationship_hpp_ */
