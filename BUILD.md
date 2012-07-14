# Building Polycode and dependencies #

Polycode uses a CMake build generator for automatically downloading and
building required 3rd party packages and Polycode itself. Polycode is
setup for preferring custom static libraries over system ones, so 
please use the dependency build system even if you have all of the
dependencies installed on your computer.

The first dependency is CMake. It can be downloaded from 
http://cmake.org/cmake/resources/software.html or installed using apt
or rpm on most Linux distributions. CMake 2.8.8 or greater is now required.

When Polycode and its Dependencies are built, they will be available
in the Release/YourArchitecture folder under the main source tree in 
a structure that should mimic the main binary release.

If you wish to build a 32-bit version on a 64-bit machine in OS X, pass
-DCMAKE_OSX_ARCHITECTURES=i386 as an argument to cmake

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

The CMake dependency build system will download and install static
version of these libraries into the Polycode source tree. It will NOT
attempt to install any of these packages into your system.

All dependenices will be installed into the Polycode source tree under
    Release/<Platform>/Framework/

Instructions describe using CMake on the command line, you
may prefer to use the CMake GUI if unfamiliar with CMake.


### Mac OS X and Xcode ###

NOTE: If you are using the new XCode that is downloaded from the AppStore
and cmake complains about not finding XCode in /Developer, you have to run this
command to update the XCode path:
sudo /usr/bin/xcode-select -switch /Applications/Xcode.app/Contents/Developer

To generate an Xcode project for building Polycode dependencies, perform
the following steps in the Polycode directory from a terminal:

    cd Dependencies
    mkdir Build
    cd Build
    cmake -G Xcode ..
    
This generates a PolycodeDependencies Xcode project in the Build 
directory. Building this project in Xcode will download, build and 
install the dependencies (make sure you build the ALL_BUILD target).
Note that you need to build both Debug and
Release in Xcode 

Note: Release is "Build for Archiving" in Xcode4.

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

### Notes ###

The Polycode CMake build will look for dependencies installed as
static libraries in the Release folder by the above
dependency build step. It will not use system level versions
of these libraries, even if you have them installed. The only exception to
this is SDL for the Linux build, which you must manually install on
the system level.

If you want to build documentation, you must have Doxygen installed 
and in your run path. You can get Doxygen from http://www.doxygen.org
or install it using a package manager. 

### Mac OS X and Xcode ###

To generate an Xcode project for building Polycode, perform the
following steps in the Polycode directory from a terminal:

    mkdir Build
    cd Build
    cmake -G Xcode ..

This generates a Polycode Xcode project in the Build directory.

Build the "ALL_BUILD" target in this project in both Debug and Release
and then build the "install" target, also in Debug and Release. This
will install Polycode into the Release/Darwin/Framework directory,
which should mirror the binary download from the website and contain
templates and examples that will build out of the box.

### Windows and Visual Studio ###

To generate a Microsoft Visual Studio project for building Polycode, 
perform the following steps in the Polycode directory from a 
command prompt:

    mkdir Build
    cd Build
    cmake -G "Visual Studio 10" ..
    
Build the "ALL_BUILD" target in this project in both Debug and Release
and then build the "install" target, also in Debug and Release. This
will install Polycode into the Release/Windows/Framework directory,
which should mirror the binary download from the website and contain
templates and examples that will build out of the box.

### Linux ###

To generate and build Debug and Release builds with Unix Makefiles 
perform the following steps in the Polycode directory from a terminal:

NOTE: You need to install SDL development libraries on your system
before doing this as they are not automatically installed by the 
Dependencies project above. You can get SDL from http://www.libsdl.org 
or using the package manager of your distribution.

    mkdir Build
    cd Build
    mkdir Debug
    cd Debug
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../..
    make
    make install
    cd ..
    mkdir Release
    cd Release
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../..
    make
    make install

This will install Polycode into the Release/Linux/Framework directory,
which should mirror the binary download from the website and contain
templates and examples that will build out of the box.

## Building Polycode Lua ##

Note: To build a complete distribution of the standalone Lua tools
as it appears in the binary release, you will need to build it on all
supported platforms and copy the module libraries and deployment
templates from all three into the folder. If you do not have access
to all the supported platforms, you will not be able to build a complete
distribution!

To build Polycode Lua, you need to build the bindings and the player,
which are disabled by default. To do this, you need to add a couple
of variables to the cmake commands above. To build the bindings, you
need a python installation with the PLY python module. You can get
the PLY module at http://www.dabeaz.com/ply/

To enable the bindings and the player, add the following options to the
cmake command. Otherwise, the steps are exactly the same as the regular 
Polycode build for your system.

    -DPOLYCODE_BUILD_BINDINGS=ON -DPOLYCODE_BUILD_PLAYER=ON

Note: You need to build the "PolycodeLua" target before you build the "install" target.

After building the install build or running 'make install', perform the
following commands in the Polycode source root:

### Mac and Linux ###

    cd Standalone
    mkdir Build
    cd Build
    cmake -G "Unix Makefiles" ..
    make install

This will create a Release/YourArchitecture/Standalone folder with the
same structure as the binary Polycode Lua release.

### Windows ###
    
    cd Standalone
    mkdir Build
    cd Build
    cmake -G "Visual Studio 10" ..

This will create a Standalone.sln solution in the Build directory. Build the
"install" target of this solution. 

This will create a Release/Windows/Standalone folder with the
same structure as the binary Polycode Lua release.

### Final steps ###

Since the standalone Lua distribution is supposed to compile packages for
all platforms, you need to do this build step on all of the platforms and
merge the Standalone/Modules and Standalone/Publish folders with the one
you just built.

## TODO ##

It would be good to create a CMake build template for people to create
new Polycode applications with.

