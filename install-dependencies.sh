#!/usr/bin/env sh

git clone https://github.com/microsoft/cpprestsdk casablanca
pushd casablanca/Release
mkdir build.release
pushd build.release
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install

popd
popd

git clone https://github.com/ruediger/libbert libbert
pushd libbert
./configure
make
sudo make install
