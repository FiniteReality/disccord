include("disccord/ws/opcode.hpp")

model{"frame",
    property{"op", "disccord::ws::opcode"},
    property{"s", "disccord::util::optional<uint32_t>"},
    property{"t", "disccord::util::optional<std::string>"},

    field{"d", "web::json::value"},

    method{"get_data", "TModel",
        [[TModel model; model.decode(d); return model;]],
        {pre = "template <typename TModel>", post = "const"}
    }
}
