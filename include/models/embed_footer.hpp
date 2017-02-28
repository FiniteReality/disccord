#ifndef _embed_footer_hpp_
#define _embed_footer_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_footer : public entity
        {
            public:
                embed_footer();
                virtual ~embed_footer();

                virtual void decode(web::json::value json) override;

                std::string get_text();
                util::optional<std::string> get_icon_url();
				util::optional<std::string> get_proxy_icon_url();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string text;
                util::optional<std::string> icon_url, proxy_icon_url;
        };
    }
}

#endif /* _embed_footer_hpp_ */