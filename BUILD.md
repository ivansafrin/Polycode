# Building Polycode and dependencies #

Polycode comes with hand maintained XCode and Visual Studio 2010 
projects which may be found in Build subdirectories under the Bindings,
Core, IDE, Modules, Player and Tools directories.

There is also a CMake build generator for automatically downloading and
building required 3rd party packages and Polycode itself.

This document describes the CMake build system for Polycode.

The first dependency is CMake. It can be downloaded from 
http://cmake.org/cmake/resources/software.html or installed using apt
or rpm on most Linux distributions. CMake 2.8.4 or greater is 
recommended.

## Building dependencies ##

Polycode depends on a number of third party packages that are not
included in the Polycode source tree:

* [Lua](http://www.lua.org/)
* [Freetype](http://www.freetype.org/)
* [zlib](http://www.zlib.net/)
* [libpng](http://www.libpng.org/pub/png/libpng.html)
* [PhysicsFS](http://icculus.org/physfs/)
* [Ogg Vorbis](http://www.vorbis.com/)
* [OpenAL](http://www.openal.org/)
* [SDL](http://www.libsdl.org/)
* [Box2D](http://www.box2d.org/)
* [Bullet Physics](http://bulletphysics.org/)
* [Assimp](http://assimp.sourceforge.net/)

Depending on your platform, some of these dependencies will already be
installed on your system. For the rest, they can be automatically 
downloaded and compiled using the CMakeLists.txt build in the 
Dependencies directory. 

The CMake dependency build will check for the existance
of dependencies and build anything that is not already installed on your
system.

All dependenices will be installed into the Polycode source tree under
    Release/<Platform>/Framework/

Instructions describe using CMake on the command line, you
may prefer to use the CMake GUI if unfamiliar with CMake.


### Mac OS X and Xcode ###

To generate an Xcode project for building Polycode dependencies, perform
the following steps in the Polycode directory from a terminal:

    cd Dependencies
    mkdir Build
    cd Build
    cmake -G Xcode ..
    
This generates a PolycodeDependencies Xcode project in the Build 
directory. Building this project in Xcode will download, build and 
install the dependencies. Note that you need to build both Debug and
Release in Xcode.

### Windows and Visual Studio ###

To generate a Microsoft Visual Studio (any version) project for building
Polycode dependencies, perform the following steps in the Polycode 
directory from a command prompt (for VS2010):

    cd Dependencies
    mkdir Build
    cd Build
    cmake -G "Visual Studio 10" ..
    
This generates a PolycodeDependencies.sln in the Build directory. 
Building this project in Visual Studio will download, build and 
install the dependencies. Note that you need to build both Debug and
Release in Visual Studio. 

### Unix Makefiles ###

Linux users should ensure available dependencies for their platform are
installed before running the Polycode dependency build. 

On a Debian system run:
    sudo apt-get install zlib1g-dev libpng12-dev libfreetype6-dev
    libphysfs-dev libogg-dev libvorbis-dev libopenal-dev libsdl1.2-dev
    liblua5.1-0-dev

To generate and build Debug and Release builds with Unix Makefiles 
perform the following steps in the Polycode directory from a terminal:

    cd Dependencies
    mkdir Build
    cd Build
    mkdir Debug
    cd Debug
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
    make
    cd ..
    mkdir Release
    cd Release
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
    make
    
## Building Polycode ##

The Polycode CMake build will look for dependencies installed on the 
system and by the above dependency build step.

### CMake variables ###

There are a number of CMake variables that can be used to control what is
built. These can be passed into CMake on the comment line as -D<name>=<value> 
or edited in the CMake GUI.

* POLYCODE_BUILD_BINDINGS 
* POLYCODE_BUILD_EXAMPLES
* POLYCODE_BUILD_MODULES
* POLYCODE_BUILD_PLAYER
* POLYCODE_BUILD_SHARED
* POLYCODE_BUILD_STATIC
* POLYCODE_BUILD_TOOLS
* POLYCODE_INSTALL_FRAMEWORK
* POLYCODE_INSTALL_PLAYER
 
### Mac OS X and Xcode ###

**Note: the Mac CMake build does not compile and link yet.**

To generate an Xcode project for building Polycode, perform the
following steps in the Polycode directory from a terminal:

    mkdir Build
    cd Build
    cmake -G Xcode ..

This generates a Polycode Xcode project in the Build directory.

### Windows and Visual Studio ###

To generate a Microsoft Visual Studio project for building Polycode, 
perform the following steps in the Polycode directory from a 
command prompt:

    mkdir Build
    cd Build
    cmake -G "Visual Studio 10" ..
    
This generates a Polycode.sln in the Build directory.

### Unix Makefiles ###

To generate and build Debug and Release builds with Unix Makefiles 
perform the following steps in the Polycode directory from a terminal:

    mkdir Build
    cd Build
    mkdir Debug
    cd Debug
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
    make
    cd ..
    mkdir Release
    cd Release
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
    make

## TODO ##

It would be good to create a CMake build template for people to create
new Polycode applications with.

Fix Mac OS X compilation and linking.
