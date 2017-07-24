model{"add_guild_member_args",
    property{"access_token", "std::string"},
    property{"nick", "disccord::util::optional<std::string>"},
    property{"roles", "std::vector<disccord::snowflake>"},
    property{"mute", "disccord::util::optional<bool>"},
    property{"deaf", "disccord::util::optional<bool>"}
}
