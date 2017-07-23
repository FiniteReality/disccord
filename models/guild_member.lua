include("disccord/models/user.hpp")

model{"guild_member",
    property{"member", "disccord::util::optional<disccord::models::user>"},
    property{"nick", "disccord::util::optional<std::string>"},
    --property{"roles", },
    --property{"joined_at", "std::chrono::time_point"},
    property{"deaf", "bool"},
    property{"mute", "bool"}
}
