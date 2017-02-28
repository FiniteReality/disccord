find_package(cpprest REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CPPREST_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CPPREST_LIBRARIES})

macro(add_test_executable name sources)
  message("-- Adding unit test group '${name}'")
  add_executable("${name}_test" "${sources}")
  add_dependencies("${name}_test" disccord)
  target_link_libraries("${name}_test" disccord ${LIBS})
  
  if(DISCCORD_IGNORE_UNSAFE_TESTS)
    add_test(NAME "${name}" COMMAND "${name}_test" -e)
  else()
    add_test(NAME "${name}" COMMAND "${name}_test")
  endif()
endmacro(add_test_executable name sources)

add_test_executable(routes routes.cpp)
add_test_executable(semaphores semaphores.cpp)
set(REST_TESTS rest.cpp models.cpp)
add_test_executable(rest "${REST_TESTS}")
