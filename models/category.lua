model{"category",
    property{"name", "std::string"},
    property{"parent_id", "disccord::util::optional<disccord::snowflake>"},
    property{"nsfw", "disccord::util::optional<bool>"},
    property{"position", "disccord::util::optional<int32_t>"},
    property{"guild_id", "disccord::util::optional<disccord::snowflake>"},
    property{"type", "disccord::channel_type"},
    property{"id", "disccord::snowflake"},
    --property{"permission_overwrites", "std::vector<disccord::models::permission_overwrite>"},
}
