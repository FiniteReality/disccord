#ifndef _guild_role_args_hpp_
#define _guild_role_args_hpp_

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace rest
    {
        namespace models
        {
            class guild_role_args : public disccord::models::model
            {
                public:
                    guild_role_args();
                    virtual ~guild_role_args();

                    void set_permissions(uint32_t permissions);
                    void set_color(uint32_t color);
                    void set_name(std::string name);
                    void set_hoist(bool hoist);
                    void set_mentionable(bool mentionable);

                protected:
                    virtual void encode_to(
                        std::unordered_map<std::string, web::json::value>& info
                    ) override;

                private:
                    util::optional<uint32_t> permissions, color;
                    util::optional<std::string> name;
                    util::optional<bool> hoist, mentionable;
            };
        }
    }
}

#endif /* _guild_role_args_hpp_ */
