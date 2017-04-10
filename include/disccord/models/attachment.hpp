#ifndef _attachment_hpp_
#define _attachment_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class attachment : public entity
        {
            public:
                attachment();
                virtual ~attachment();

                virtual void decode(web::json::value json) override;

                std::string get_filename();
                std::string get_url();
                util::optional<std::string> get_proxy_url();
                util::optional<uint16_t> get_height();
                util::optional<uint16_t> get_width();
                int32_t get_size();

            protected:
                virtual void encode_to(std::unordered_map<std::string,web::json::value> &info) override;

            private:
                std::string filename, url;
                util::optional<std::string> proxy_url;
                util::optional<uint16_t> height, width;
                int32_t size;
        };
    }
}

#endif /* _attachment_hpp_ */
