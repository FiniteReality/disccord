#ifndef _execute_webhook_args_hpp_
#define _execute_webhook_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/models/embed.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class execute_webhook_args : public disccord::models::model
            {
                public:
                    execute_webhook_args(std::string content);
                    execute_webhook_args(std::vector<disccord::models::embed> embeds);
                    virtual ~execute_webhook_args();

                    void set_username(std::string username);
                    void set_avatar_url(std::string avatar_url);
                    void set_tts(bool tts);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> content, username, avatar_url;
                    util::optional<bool> tts;
                    util::optional<std::vector<disccord::models::embed>> embeds;
            };
        }
    }
}

#endif /* _execute_webhook_args_hpp_ */
