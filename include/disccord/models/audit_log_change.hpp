#ifndef _audit_log_change_hpp_
#define _audit_log_change_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace models
    {
        class audit_log_change : public model
        {
            public:
                audit_log_change();
                virtual ~audit_log_change();

                virtual void decode(web::json::value json) override;

                std::string get_key();
                std::string get_new_value();
                util::optional<std::string> get_old_value();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string key, new_value;
                util::optional<std::string> old_value;
        };
    } // namespace models
} // namespace disccord

#endif /* _audit_log_change_hpp_ */
