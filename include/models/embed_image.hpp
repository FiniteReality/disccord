#ifndef _embed_image_hpp_
#define _embed_image_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_image : public model
        {
            public:
                embed_image();
                virtual ~embed_image();

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

#endif /* _embed_image_hpp_ */
