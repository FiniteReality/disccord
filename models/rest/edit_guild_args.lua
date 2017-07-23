model{"edit_guild_args",
    -- ????
    property{"username", "disccord::util::optional<std::string>"},
    property{"name", "disccord::util::optional<std::string>"},
    property{"region", "disccord::util::optional<std::string>"},
    property{"verification_level", "disccord::util::optional<disccord::verification_level>"},
    property{"default_message_notifications", "disccord::util::optional<disccord::notification_level>"},
    property{"afk_timeout", "disccord::util::optional<uint32_t>"},
    property{"icon", "disccord::util::optional<std::string>"},
    property{"splash", "disccord::util::optional<std::string>"},
    property{"afk_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"owner_id", "disccord::util::optional<disccord::snowflake>"},
}
