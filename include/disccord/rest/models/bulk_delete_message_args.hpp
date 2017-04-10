#ifndef _bulk_delete_message_args_hpp_
#define _bulk_delete_message_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class bulk_delete_message_args : public disccord::models::model
            {
                public:
                    bulk_delete_message_args(std::vector<uint64_t> message_ids);
                    virtual ~bulk_delete_message_args();

                protected:
                    virtual void encode_to(std::unordered_map<std::string, web::json::value>& info) override;

                private:
                    std::vector<uint64_t> message_ids;
            };
        }
    }
}

#endif /* _bulk_delete_message_args_hpp_ */
