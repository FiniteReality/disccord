#!/usr/bin/env sh

git clone https://github.com/microsoft/cpprestsdk casablanca
cd casablanca/Release
mkdir build.release
cd build.release
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
