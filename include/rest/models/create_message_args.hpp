#ifndef _create_message_args_hpp_
#define _create_message_args_hpp_

#include <models/model.hpp>
#include <models/embed.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class create_message_args : public disccord::models::model
            {
                public:
                    create_message_args(std::string content);
                    virtual ~create_message_args();

                    std::string get_content();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string content;
            };
        }
    }
}

#endif /* _create_message_args_hpp_ */
