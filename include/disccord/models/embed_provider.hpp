#ifndef _embed_provider_hpp_
#define _embed_provider_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_provider : public model
        {
            public:
                embed_provider();
                virtual ~embed_provider();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                util::optional<std::string> get_url();

            protected:
                virtual void encode_to(
                    std::unordered_map<std::string, web::json::value> &info
                ) override;

            private:
                std::string name;
                util::optional<std::string> url;
        };
    }
}

#endif /* _embed_provider_hpp_ */
