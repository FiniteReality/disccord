--include("disccord/models/embed.hpp")

model{"create_message_args",
    property{"content", "std::string"},
    property{"nonce", "disccord::util::optional<std::string>"},
    property{"tts", "disccord::util::optional<bool>"},
    --property{"embed", "disccord::util::optional<disccord::models::embed>"}
}
