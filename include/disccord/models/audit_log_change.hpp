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
        template <typename T>
        T get_new_value()
        {
            return new_value;
        }
        template <typename T>
        util::optional<T> get_old_value()
        {
            return old_value;
        }

    protected:
        virtual void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

    private:
        std::string key;
        template <typename T>
        T new_value;
        template <typename T>
        util::optional<T> old_value;
};
} // namespace models
} // namespace disccord

#endif /* _audit_log_change_hpp_ */
