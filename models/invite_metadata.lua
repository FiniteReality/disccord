include("disccord/models/user.hpp")

model{"invite_metadata",
    property{"inviter", "disccord::models::user"},
    property{"uses", "uint32_t"},
    property{"max_uses", "uint32_t"},
    property{"max_age", "uint32_t"},
    property{"temporary", "bool"},
    --property{"created_at", "std::chrono::time_point"},
    property{"revoked", "bool"}
}
