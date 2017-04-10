#ifndef _create_message_args_hpp_
#define _create_message_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/models/embed.hpp>
#include <disccord/util/optional.hpp>

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

                    void set_nonce(uint64_t nonce);
                    void set_tts(bool tts);
                    void set_embed(disccord::models::embed embed);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::string content;
                    util::optional<uint64_t> nonce;
                    util::optional<bool> tts;
                    util::optional<disccord::models::embed> embed;
            };
        }
    }
}

#endif /* _create_message_args_hpp_ */
