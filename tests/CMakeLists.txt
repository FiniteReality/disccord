<<<<<<< HEAD
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(test_memory disccord_test.cpp)
add_dependencies(test_memory disccord)
target_link_libraries(test_memory disccord)

add_test(NAME memory COMMAND test_memory)
=======
find_package(cpprest REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CPPREST_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES})

macro(add_test_executable name source)
  message("-- Adding unit test group '${name}'")
  add_executable("${name}_test" "${source}")
  add_dependencies("${name}_test" disccord)
  target_link_libraries("${name}_test" disccord ${LIBS})
  add_test(NAME "${name}" COMMAND "${name}_test")
endmacro(add_test_executable)

add_test_executable(routes routes.cpp)
add_test_executable(semaphores semaphores.cpp)
add_test_executable(rest rest.cpp)
>>>>>>> 6cd5efc8180f534604e0446d926ade4e351943a8
