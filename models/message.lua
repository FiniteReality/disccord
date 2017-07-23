include("disccord/models/user.hpp")

model{"message",
    property{"id", "disccord::snowflake"},
    -- ????? i'm getting json where this is null
    property{"type", "disccord::message_type"},
    property{"channel_id", "disccord::snowflake"},
    property{"webhook_id", "disccord::util::optional<disccord::snowflake>"},
    property{"author", "disccord::util::optional<disccord::models::user>"},
    property{"content", "disccord::util::optional<std::string>"},
    --property{"timestamp", "disccord::util::optional<std::chrono::time_point>"},
    --property{"edited_timestamp", "disccord::util::optional<std::chrono::time_point>"},
    property{"tts", "disccord::util::optional<bool>"},
    property{"mention_everyone", "disccord::util::optional<bool>"},
    --property{"mentions", },
    --property{"mention_roles", },
    --property{"attachments", },
    --property{"embeds", },
    property{"pinned", "disccord::util::optional<bool>"},
    --property{"reactions", }
}
