model{"user",
    property{"id", "disccord::snowflake"},
    property{"username", "std::string"},
    property{"discriminator", "disccord::discriminator"},
    property{"avatar", "disccord::util::optional<std::string>"},
    property{"bot", "disccord::util::optional<bool>"},
    property{"mfa_enabled", "disccord::util::optional<bool>"},
    property{"verified", "disccord::util::optional<bool>"},
    property{"email", "disccord::util::optional<std::string>"}
}
