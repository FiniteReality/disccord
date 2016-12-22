cmake_minimum_required(VERSION 3.1)

project(disccord)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-sign-append")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DISCCORD_BUILD_STATIC "build disccord as a static library" OFF)

add_subdirectory(lib)
add_subdirectory(tests)
enable_testing ()

## add all relevant unit tests here
add_test (NAME libdisscord_test COMMAND DisccordTest)