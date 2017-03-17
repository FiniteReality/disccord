#ifndef _invite_channel_hpp_
#define _invite_channel_hpp_

#include <models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class invite_channel : public model
        {
            public:
                invite_channel();
                virtual ~invite_channel();

                virtual void decode(web::json::value json) override;

                uint64_t get_id();
                std::string get_name();
                std::string get_type();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                uint64_t id;
                std::string name, type;
        };
    }
}

#endif /* _invite_channel_hpp_ */
