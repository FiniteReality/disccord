cmake_minimum_required(VERSION 3.1)

project(disccord)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DISCCORD_BUILD_STATIC "build disccord as a static library" OFF)
option(DISCCORD_BUILD_TESTS "build disccord tests" ON)
option(DISCCORD_BUILD_SAMPLES "build disccord samples" ON)
option(DISCCORD_IGNORE_UNSAFE_TESTS "ignore tests which may cause errors" OFF)

add_subdirectory(lib)

if(DISCCORD_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (DISCCORD_BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
