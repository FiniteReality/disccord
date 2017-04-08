#ifndef _modify_channel_args_hpp_
#define _modify_channel_args_hpp_

#include <models/model.hpp>
#include <util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class modify_channel_args : public disccord::models::model
            {
                public:
                    modify_channel_args();
                    virtual ~modify_channel_args();

                    void set_name(std::string name);
                    void set_topic(std::string topic);
                    void set_position(uint16_t position);
                    void set_user_limit(uint16_t user_limit);
                    void set_bitrate(uint32_t bitrate);

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    util::optional<std::string> name, topic;
                    util::optional<uint16_t> position, user_limit;
                    util::optional<uint32_t> bitrate;
            };
        }
    }
}

#endif /* _modify_channel_args_hpp_ */
