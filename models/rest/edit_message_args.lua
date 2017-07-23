--include("disccord/models/embed.hpp")

model{"edit_message_args",
    property{"content", "disccord::util::optional<std::string>"},
    --property{"embed", "disccord::util::optional<disccord::models::embed>"}
}
