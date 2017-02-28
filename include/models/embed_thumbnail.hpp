#ifndef _embed_thumbnail_hpp_
#define _embed_thumbnail_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_thumbnail : public entity
        {
            public:
                embed_thumbnail();
                virtual ~embed_thumbnail();

                virtual void decode(web::json::value json) override;

                std::string get_url();
                util::optional<std::string> get_proxy_url();
                util::optional<int> get_height();
                util::optional<int> get_width();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string url;
                util::optional<std::string> proxy_url;
                util::optional<int> height, width;
        };
    }
}

#endif /* _embed_thumbnail_hpp_ */