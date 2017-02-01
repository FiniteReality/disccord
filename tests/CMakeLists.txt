find_package(Boost COMPONENTS system filesystem REQUIRED)

macro(add_test_executable name source)
  message("-- Adding unit test group '${name}'")
  add_executable("${name}_test" "${source}")
  add_dependencies("${name}_test" disccord)
  target_link_libraries("${name}_test" disccord)
  add_test(NAME name COMMAND "${name}_test")
endmacro(add_test_executable)

add_test_executable(routes routes.cpp)