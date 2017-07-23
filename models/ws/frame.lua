include("disccord/ws/opcode.hpp")

model{"frame",
    property{"opcode", "disccord::ws::opcode"},
    property{"sequence", "disccord::util::optional<uint32_t>"},
    property{"event", "disccord::util::optional<std::string>"},

    field{"data", "web::json::value"},

    method{"get_data", "TModel",
        [[TModel model; model.decode(data); return model;]],
        {pre = "template <typename TModel>", post = "const"}
    }
}
