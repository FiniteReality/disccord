include("disccord/models/user.hpp")

model{"ban",
    property{"user", "disccord::models::user"},
    property{"reason", "std::string"}
}
