include("disccord/models/user.hpp")

model{"application",
    property{"description", "std::string"},
    property{"rpc_origins", "std::vector<std::string>"},
    property{"name", "std::string"},
    property{"id", "disccord::snowflake"},
    property{"icon", "std::string"},
    property{"flags", "disccord::util::optional<uint64_t>"},
    property{"owner", "disccord::util::optional<disccord::models::user>"}
}
