#ifndef _gateway_info_hpp_
#define _gateway_info_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace models
    {
        class gateway_info : public model
        {
            public:
                gateway_info();
                virtual ~gateway_info();

                virtual void decode(web::json::value json) override;

                std::string get_url();
                util::optional<int> get_shards();

            private:
                std::string url;
                util::optional<int> shards;
        };
    }
}

#endif /* _gateway_info_hpp_*/
