include("disccord/models/user.hpp")

model{"integration",
    property{"id", "disccord::snowflake"},
    property{"name", "std::string"},
    property{"type", "std::string"},
    property{"enabled", "bool"},
    property{"syncing", "bool"},
    property{"role_id", "disccord::snowflake"},
    property{"expire_behaviour", "uint64_t"},
    property{"expire_grace_period", "uint64_t"},
    property{"user", "disccord::models::user"},
    --property{"account", "disccord::models::integration_account"},
    --property{"synced_at", "std::chrono::time_point"}
}
