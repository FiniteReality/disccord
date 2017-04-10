#ifndef _voice_region_hpp_
#define _voice_region_hpp_

#include <disccord/models/entity.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace models
    {
        class voice_region : public model
        {
            public:
                voice_region();
                virtual ~voice_region();

                virtual void decode(web::json::value json) override;

                std::string get_id();
                std::string get_name();
                util::optional<std::string> get_sample_hostname();
                util::optional<uint32_t> get_sample_port();
                bool get_vip();
                bool get_optimal();
                bool get_deprecated();
                bool get_custom();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string id, name;
                util::optional<std::string> sample_hostname;
                util::optional<uint32_t> sample_port;
                bool vip, optimal, deprecated, custom;
        };
    }
}

#endif /* _voice_region_hpp_ */
