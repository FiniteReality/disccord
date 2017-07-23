converter{
    from = "disccord::verification_level",
    to = "uint32_t",
    "static_cast<uint32_t>(%s)"
}
converter{
    from = "disccord::notification_level",
    to = "uint32_t",
    "static_cast<uint32_t>(%s)"
}
converter{
    from = "disccord::mfa_level",
    to = "uint32_t",
    "static_cast<uint32_t>(%s)"
}
converter{
    from = "uint32_t",
    to = "disccord::verification_level",
    "static_cast<disccord::verification_level>(%s)"
}
converter{
    from = "uint32_t",
    to = "disccord::notification_level",
    "static_cast<disccord::notification_level>(%s)"
}
converter{
    from = "uint32_t",
    to = "disccord::mfa_level",
    "static_cast<disccord::mfa_level>(%s)"
}

model{"guild",
    property{"id", "disccord::snowflake"},
    property{"name", "std::string"},
    property{"icon", "disccord::util::optional<std::string>"},
    property{"splash", "disccord::util::optional<std::string>"},
    property{"owner_id", "disccord::snowflake"},
    property{"region", "std::string"},
    property{"afk_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"afk_timeout", "disccord::util::optional<uint32_t>"},
    property{"embed_enabled", "bool"},
    property{"embed_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"verification_level", "disccord::verification_level"},
    property{"default_message_notifications", "disccord::notification_level"},
    --property{"roles", }
    --property{"emojis", }
    --property{"features", }
    property{"mfa_level", "disccord::mfa_level"},
    property{"application_id", "disccord::util::optional<disccord::snowflake>"},
    --property{"joined_at", "disccord::util::optional<std::chrono::time_point>"},
    property{"large", "disccord::util::optional<bool>"},
    property{"unavailable", "disccord::util::optional<bool>"},
    property{"member_count", "disccord::util::optional<uint32_t>"},
    --property{"voice_states", }
    --property{"members", }
    --property{"channels", }
    --property{"presences", }
}
