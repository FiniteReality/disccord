#ifndef _embed_video_hpp_
#define _embed_video_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class embed_video : public model
        {
            public:
                embed_video();
                virtual ~embed_video();

                virtual void decode(web::json::value json) override;

                std::string get_url();
                util::optional<int> get_height();
                util::optional<int> get_width();

            protected:
                virtual void encode_to(
                    std::unordered_map<std::string, web::json::value> &info
                ) override;

            private:
                std::string url;
                util::optional<int> height, width;
        };
    }
}

#endif /* _embed_video_hpp_ */
