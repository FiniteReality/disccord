#ifndef _embed_author_hpp_
#define _embed_author_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_author : public entity
        {
            public:
                embed_author();
                virtual ~embed_author();

                virtual void decode(web::json::value json) override;

                std::string get_name();
                util::optional<std::string> get_url();
                util::optional<std::string> get_icon_url();
				util::optional<std::string> get_proxy_icon_url();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string name;
                util::optional<std::string> url, icon_url, proxy_icon_url;
        };
    }
}

#endif /* _embed_author_hpp_ */