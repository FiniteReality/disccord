#ifndef _invite_metadata_hpp_
#define _invite_metadata_hpp_

#include <models/entity.hpp>
#include <models/user.hpp>

namespace disccord
{
    namespace models
    {
        class invite_metadata : public model
        {
            public:
                invite_metadata();
                virtual ~invite_metadata();

                virtual void decode(web::json::value json) override;

                util::optional<user> get_inviter();
                std::string get_created_at();
                uint32_t get_uses();
                uint32_t get_max_uses();
                uint32_t get_max_age();
                bool get_temporary();
                bool get_revoked();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                util::optional<user> inviter;
                std::string created_at;
                uint32_t uses, max_uses, max_age;
                bool temporary, revoked;
        };
    }
}

#endif /* _invite_metadata_hpp_ */
