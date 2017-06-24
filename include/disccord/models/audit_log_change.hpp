#ifndef _audit_log_change_hpp_
#define _audit_log_change_hpp_

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include <disccord/models/entity.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace models
    {
        class roles_change: public entity // class wrapping role updates (from the change key $add or $remove)
        {
            public:
                roles_change();
                virtual ~roles_change();
                
                virtual void decode(web::json::value json) override;
                
                std::string get_name();
                
            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;
                
            private:
                std::string name;
        };
        
        class audit_log_change : public model
        {
            public:
                using change_value = boost::variant<uint64_t, std::string, bool, std::vector<roles_change>>;

                audit_log_change();
                virtual ~audit_log_change();

                virtual void decode(web::json::value json) override;

                std::string get_key();
                util::optional<change_value> get_new_value();
                util::optional<change_value> get_old_value();

            protected:
                virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

            private:
                std::string key;
                util::optional<change_value> new_value, old_value;
        };
    } // namespace models
} // namespace disccord

#endif /* _audit_log_change_hpp_ */
