include("disccord/models/channel.hpp")
include("disccord/models/guild_member.hpp")
include("disccord/models/role.hpp")

model{"guild",
    property{"id", "disccord::snowflake"},
    property{"name", "std::string"},
    property{"icon", "disccord::util::optional<std::string>"},
    property{"splash", "disccord::util::optional<std::string>"},
    property{"owner_id", "disccord::snowflake"},
    property{"region", "std::string"},
    property{"afk_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"system_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"afk_timeout", "disccord::util::optional<uint32_t>"},
    property{"embed_enabled", "bool"},
    property{"embed_channel_id", "disccord::util::optional<disccord::snowflake>"},
    property{"verification_level", "disccord::verification_level"},
    property{"default_message_notifications", "disccord::notification_level"},
    property{"roles", "std::vector<disccord::models::role>"},
    --property{"emojis", "std::vector<disccord::models::emoji>"},
    property{"features", "std::vector<std::string>"},
    property{"mfa_level", "disccord::mfa_level"},
    property{"application_id", "disccord::util::optional<disccord::snowflake>"},
    --property{"joined_at", "disccord::util::optional<std::chrono::time_point>"},
    property{"large", "disccord::util::optional<bool>"},
    property{"unavailable", "disccord::util::optional<bool>"},
    property{"member_count", "disccord::util::optional<uint32_t>"},
    --property{"voice_states", "std::vector<disccord::models::voice_state>"}
    property{"members", "std::vector<disccord::models::guild_member>"},
    property{"channels", "std::vector<disccord::models::channel>"},
    --property{"presences", "std::vector<disccord::models::presence>"}
}
