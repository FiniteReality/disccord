#ifndef _modify_current_user_args_hpp_
#define _modify_current_user_args_hpp_

#include <cpprest/http_client.h>

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

using namespace Concurrency::streams;
using namespace utility::conversions;

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_current_user_args : public disccord::models::model
            {
                public:
                    modify_current_user_args();
                    virtual ~modify_current_user_args();

                    void set_name(std::string name);
                    //avatar_stream -> file_stream<unsigned char>::open_istream(<filename>).get()
                    //NOTE: using an unsigned char stream because the to_base64 method takes a std::vector<unsigned char>
                    void set_avatar(basic_istream<unsigned char> avatar_stream);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> name, avatar;
            };
        }
    }
}

#endif /* _modify_current_user_args_hpp_ */
