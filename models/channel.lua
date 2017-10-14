include("disccord/models/user.hpp")

model{"channel",
    -- All channels
    property{"id", "disccord::snowflake"},
    property{"type", "disccord::channel_type"},
    -- Guild channels
    property{"guild_id", "disccord::util::optional<disccord::snowflake>"},
    property{"position", "disccord::util::optional<int32_t>"},
    property{"name", "disccord::util::optional<std::string>"},
    property{"parent_id", "disccord::util::optional<disccord::snowflake>"},
    property{"nsfw", "disccord::util::optional<bool>"},
    --property{"permission_overwrites", "std::vector<disccord::models::pemrission_overwrite>"},
    -- Text channels
    property{"topic", "disccord::util::optional<std::string>"},
    --property{"last_pin_timestamp", "disccord::util::optional<std::chrono::time_point>"},
    property{"last_message_id", "disccord::util::optional<disccord::snowflake>"},
    -- Voice channels
    property{"bitrate", "disccord::util::optional<int32_t>"},
    property{"user_limit", "disccord::util::optional<int32_t>"},
    -- DM channels
    property{"recipients", "std::vector<disccord::models::user>"},
    property{"icon", "disccord::util::optional<std::string>"},
    property{"owner_id", "disccord::util::optional<disccord::snowflake>"},
    property{"application_id", "disccord::util::optional<disccord::snowflake>"}
}