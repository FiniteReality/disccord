#ifndef _embed_hpp_
#define _embed_hpp_

#include <vector>

#include <disccord/models/entity.hpp>
#include <disccord/models/embed_author.hpp>
#include <disccord/models/embed_field.hpp>
#include <disccord/models/embed_footer.hpp>
#include <disccord/models/embed_image.hpp>
#include <disccord/models/embed_video.hpp>
#include <disccord/models/embed_thumbnail.hpp>
#include <disccord/models/embed_provider.hpp>

namespace disccord
{
    namespace models
    {
        class embed : public model
        {
            public:
                embed();
                virtual ~embed();

                virtual void decode(web::json::value json) override;

                std::string get_title();
                std::string get_type();
                util::optional<std::string> get_description();
                util::optional<std::string> get_url();
                util::optional<std::string> get_timestamp();
                int get_color();
                util::optional<embed_footer> get_footer();
                util::optional<embed_image> get_image();
                util::optional<embed_thumbnail> get_thumbnail();
                util::optional<embed_video> get_video();
                util::optional<embed_provider> get_provider();
                util::optional<embed_author> get_author();
                util::optional<std::vector<embed_field>> get_fields();

            protected:
                virtual void encode_to(
                    std::unordered_map<std::string, web::json::value> &info
                ) override;

            private:
                std::string title, type;
                util::optional<std::string> description, url, timestamp;
                int color;
                util::optional<embed_footer> footer;
                util::optional<embed_image> image;
                util::optional<embed_thumbnail> thumbnail;
                util::optional<embed_video> video;
                util::optional<embed_provider> provider;
                util::optional<embed_author> author;
                util::optional<std::vector<embed_field>> fields;
        };
    }
}

#endif /* _embed_hpp_ */
