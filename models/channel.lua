converter{
    from = "uint32_t",
    to = "disccord::channel_type",
    "static_cast<disccord::channel_type>(%s)"
}
converter{
    from = "disccord::channel_type",
    to = "uint32_t",
    "static_cast<uint32_t>(%s)"
}

model{"channel",
    -- All channels
    property{"id", "disccord::snowflake"},
    property{"type", "disccord::channel_type"},
    -- Guild channels
    property{"guild_id", "disccord::util::optional<disccord::snowflake>"},
    property{"position", "disccord::util::optional<int32_t>"},
    --property{"permission_overwrites", },
    property{"name", "disccord::util::optional<std::string>"},
    -- Text channels
    property{"topic", "disccord::util::optional<std::string>"},
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
