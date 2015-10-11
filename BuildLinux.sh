#!/bin/bash
# ~/bin/build-polycode
set -euv
basedir=$(pwd)

# NOTE: The build system does not install any files into CMAKE_INSTALL_PREFIX,
# but instead builds everything in the source tree.

# You can supply parameters to make by passing them as parameters to this
# script. For example -j<number of threads> may be useful.

# Build dependencies

mkdir -p "$basedir/Dependencies/Build/Debug"
cd       "$basedir/Dependencies/Build/Debug"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
make $@

mkdir -p "$basedir/Dependencies/Build/Release"
cd       "$basedir/Dependencies/Build/Release"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
make $@

# Build core

mkdir -p "$basedir/Build/Debug"
cd       "$basedir/Build/Debug"
cmake -G "Unix Makefiles" -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON -DCMAKE_BUILD_TYPE=Debug -DPYTHON_EXECUTABLE=/usr/bin/python2 ../..
make $@
make $@ PolycodeLua
make install

mkdir -p "$basedir/Build/Release"
cd       "$basedir/Build/Release"
cmake -G "Unix Makefiles" -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON -DCMAKE_BUILD_TYPE=Release -DPYTHON_EXECUTABLE=/usr/bin/python2 ../..
make $@
make $@ PolycodeLua
make install

# Build standalone

mkdir -p "$basedir/Standalone/Build"
cd       "$basedir/Standalone/Build"
cmake -G "Unix Makefiles" ..
make install

# Build IDE

mkdir -p "$basedir/IDE/Build/Linux"
cd       "$basedir/IDE/Build/Linux"
make $@
# IDE executable is found in "$basedir/IDE/Build/Linux/Build"


