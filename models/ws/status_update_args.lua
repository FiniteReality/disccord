include("disccord/models/game.hpp")

model{"status_update_args",
    property{"status", "std::string"},
    property{"game", "disccord::models::game"},
    property{"afk", "bool"},
    property{"since", "disccord::util::optional<uint64_t>"}
}
