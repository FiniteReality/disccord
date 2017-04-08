#ifndef _edit_message_args_hpp_
#define _edit_message_args_hpp_

#include <models/model.hpp>
#include <models/embed.hpp>
#include <util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class edit_message_args : public disccord::models::model
            {
                public:
                    edit_message_args();
                    virtual ~edit_message_args();

                    void set_content(std::string content);
                    void set_embed(disccord::models::embed embed);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> content;
                    util::optional<disccord::models::embed> embed;
            };
        }
    }
}

#endif /* _edit_message_args_hpp_ */

