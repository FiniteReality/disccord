#!/usr/bin/env sh

if [ -d "./build" ]; then
    mkdir build
fi

cd build

# if we are not a travis CI build
if [ "$TRAVIS" -eq "true" -a "$TRAVIS_PULL_REQUEST_SHA" -eq "" ]; then
    cmake ..
else
    cmake .. -DDISCCORD_IGNORE_UNSAFE_TESTS=1
fi

make
