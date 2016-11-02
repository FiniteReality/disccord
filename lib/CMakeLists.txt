set(SOURCE_FILES client.cpp)

add_library(disccord SHARED ${SOURCE_FILES})

target_include_directories(disccord PUBLIC ../include)
