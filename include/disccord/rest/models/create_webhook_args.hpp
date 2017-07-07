#ifndef _create_webhook_args_hpp_
#define _create_webhook_args_hpp_

#include <cpprest/streams.h>
#include <cpprest/containerstream.h>

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_webhook_args : public disccord::models::model
            {
                public:
                    create_webhook_args(std::string name);
                    virtual ~create_webhook_args();

                    void set_name(std::string name);
                    void set_avatar(concurrency::streams::basic_istream<unsigned char> avatar_stream);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string name;
                    util::optional<std::string> avatar;
            };
        }
    }
}

#endif /* _create_webhook_args_hpp_ */
