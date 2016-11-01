# I have *literally* no idea what I'm doing.
# Know any better? Feel free to correct my (probably) awful mistakes.
# :)

cmake_minimum_required(VERSION 3.1)

project(disccord)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wno-sign-append") # I added these flags, change them if you don't like them
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++14 and up only!

add_subdirectory(lib)
