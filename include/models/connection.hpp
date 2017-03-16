#ifndef _connection_hpp_
#define _connection_hpp_

#include <models/entity.hpp>
#include <models/integration.hpp>

namespace disccord
{
    namespace models
    {
        class connection : public model
        {
            public:
                connection();
                virtual ~connection();

                virtual void decode(web::json::value json) override;

                std::string get_id();
                std::string get_name();
                std::string get_type();
                bool get_revoked();
                util::optional<std::vector<integration>> get_integrations();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string id, name, type;
                bool revoked;
                util::optional<std::vector<integration>> integrations;
        };
    }
}

#endif /* _connection_hpp_ */
