#!/bin/bash
# ~/bin/build-polycode

mkdir -p Dependencies/Build/Debug Dependencies/Build/Release Build/Debug Build/Release Standalone/Build
cd Dependencies/Build/Debug
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
make
cd ../Release
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
make
cd ../../../Build/Debug
cmake -G "Unix Makefiles" -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON -DCMAKE_BUILD_TYPE=Debug -DPYTHON_EXECUTABLE=/usr/bin/python2 ../..
make
make install
cd ../Release
cmake -G "Unix Makefiles" -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON -DCMAKE_BUILD_TYPE=Release -DPYTHON_EXECUTABLE=/usr/bin/python2 ../..
make
make install
cd ../../Standalone/Build
cmake -G "Unix Makefiles" ..
make install
