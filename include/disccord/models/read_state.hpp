#ifndef _read_state_hpp_
#define _read_state_hpp_

#include <disccord/models/entity.hpp>

namespace disccord
{
    namespace models
    {
        class read_state : public entity
        {
            public:
                read_state();
                virtual ~read_state();

                virtual void decode(web::json::value json) override;

                uint32_t get_mention_count();
                util::optional<uint64_t> get_last_message_id();

            protected:
                virtual void encode_to(
                    std::unordered_map<std::string, web::json::value> &info
                ) override;

            private:
                uint32_t mention_count;
                util::optional<uint64_t> last_message_id;
        };
    }
}

#endif /* _read_state_hpp_ */
