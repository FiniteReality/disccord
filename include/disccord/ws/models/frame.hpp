#ifndef _frame_hpp_
#define _frame_hpp_

#include <string>

#include <disccord/models/model.hpp>
#include <disccord/util/optional.hpp>

namespace disccord
{
    namespace ws
    {
        namespace models
        {
            class frame : public disccord::models::model
            {
                public:
                    frame();
                    virtual ~frame();

                    void decode(web::json::value json) override;

                    int get_opcode() const;
                    util::optional<int> get_sequence() const;
                    util::optional<std::string> get_event() const;

                    template <typename TModel>
                    TModel get_data() const
                    {
                        TModel model;
                        model.decode(data);
                        return model;
                    }

                protected:
                    void encode_to(std::unordered_map<std::string, web::json::value> &info) override;

                private:
                    int opcode;
                    web::json::value data;
                    util::optional<int> sequence;
                    util::optional<std::string> event;
            };
        }
    }
}

#endif /* _frame_hpp_ */
