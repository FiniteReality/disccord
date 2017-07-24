include("disccord/models/role.hpp")
include("disccord/models/user.hpp")

model{"message",
    property{"id", "disccord::snowflake"},
    property{"type", "disccord::message_type"},
    property{"channel_id", "disccord::snowflake"},
    property{"webhook_id", "disccord::util::optional<disccord::snowflake>"},
    property{"author", "disccord::util::optional<disccord::models::user>"},
    property{"content", "disccord::util::optional<std::string>"},
    --property{"timestamp", "disccord::util::optional<std::chrono::time_point>"},
    --property{"edited_timestamp", "disccord::util::optional<std::chrono::time_point>"},
    property{"tts", "disccord::util::optional<bool>"},
    property{"mention_everyone", "disccord::util::optional<bool>"},
    property{"mentions", "std::vector<disccord::models::user>"},
    property{"mention_roles", "std::vector<disccord::models::role>"},
    --property{"attachments", "std::vector<disccord::models::attachment>"},
    --property{"embeds", "std::vector<disccord::models::embed>"},
    property{"pinned", "disccord::util::optional<bool>"},
    --property{"reactions", "std::vector<disccord::models::reaction>"}
}
