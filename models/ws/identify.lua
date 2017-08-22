model{"identify",
    property{"token", "std::string"},
    property{"properties", "web::json::value"},
    property{"compress", "bool"},
    property{"large_threshold", "uint8_t"},
    property{"shard", "std::vector<uint32_t>"},
    -- presence not implemented yet
    --property{"presence", "disccord::util::optional"}
}
