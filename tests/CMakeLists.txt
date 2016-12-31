find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(test_memory disccord_test.cpp)
add_dependencies(test_memory disccord)
target_link_libraries(test_memory disccord)

add_test(NAME memory COMMAND test_memory)
