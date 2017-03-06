#!/usr/bin/env sh

if ! [ -d "./build" ]; then
    mkdir build
fi

cd build

# if we are not a travis CI PR build
if [ "$TRAVIS" = "true" -a "$TRAVIS_PULL_REQUEST_SHA" = "" ]; then
    cmake ..
else
    cmake .. -DDISCCORD_IGNORE_UNSAFE_TESTS=1
fi

make
ctest -VV
