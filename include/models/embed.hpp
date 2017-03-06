#ifndef _embed_hpp_
#define _embed_hpp_

#include <vector>

#include <models/entity.hpp>
#include <models/embed_author.hpp>
#include <models/embed_field.hpp>
#include <models/embed_footer.hpp>
#include <models/embed_image.hpp>
#include <models/embed_video.hpp>
#include <models/embed_thumbnail.hpp>
#include <models/embed_provider.hpp>

namespace disccord
{
    namespace models
    {
        class embed : public entity
        {
            public:
                embed();
                virtual ~embed();

                virtual void decode(web::json::value json) override;
                
                void set_footer(web::json::value json);
                void set_image(web::json::value json);
                void set_thumbnail(web::json::value json);
                void set_video(web::json::value json);
                void set_provider(web::json::value json);
                void set_author(web::json::value json);
                void add_field(web::json::value json);

                std::string get_title();
                std::string get_type();
                util::optional<std::string> get_description();
                util::optional<std::string> get_url();
                util::optional<std::string> get_date();
                int get_color();
                util::optional<embed_footer> get_footer();
                util::optional<embed_image> get_image();
                util::optional<embed_thumbnail> get_thumbnail();
                util::optional<embed_video> get_video();
                util::optional<embed_provider> get_provider();
                util::optional<embed_author> get_author();
                util::optional<std::vector<embed_field>> get_fields();
                
            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string title, type;
                util::optional<std::string> description, url, date;
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
