model{"channel",
    -- All channels
    property{"id", "disccord::snowflake"},
    -- ????? i'm getting json where this is null
    property{"type", "disccord::util::optional<disccord::channel_type>"},
    -- Guild channels
    property{"guild_id", "disccord::util::optional<disccord::snowflake>"},
    property{"position", "disccord::util::optional<int32_t>"},
    property{"name", "disccord::util::optional<std::string>"},
    --property{"permission_overwrites", },
    -- Text channels
    property{"topic", "disccord::util::optional<std::string>"},
    --property{"last_pin_timestamp", "disccord::util::optional<std::chrono::time_point>"},
    property{"last_message_id", "disccord::util::optional<disccord::snowflake>"},
    -- Voice channels
    property{"bitrate", "disccord::util::optional<int32_t>"},
    property{"user_limit", "disccord::util::optional<int32_t>"},
    -- DM channels
    --property{"recipients", },
    property{"icon", "disccord::util::optional<std::string>"},
    property{"owner_id", "disccord::util::optional<disccord::snowflake>"},
    property{"application_id", "disccord::util::optional<disccord::snowflake>"}
}
