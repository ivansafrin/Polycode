CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(PolyCode)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug")
#   SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

# Options for what components to build
OPTION(POLYCODE_BUILD_SHARED "Build Polycode shared libraries" ON)
OPTION(POLYCODE_BUILD_STATIC "Build Polycode static libraries" OFF)
OPTION(POLYCODE_BUILD_BINDINGS "Build Polycode Lua bindings" ON)
OPTION(POLYCODE_BUILD_EXAMPLES "Build Polycode examples" ON)
OPTION(POLYCODE_BUILD_MODULES "Build Polycode modules" ON)
OPTION(POLYCODE_BUILD_PLAYER "Build Polycode standalone player" ON)
OPTION(POLYCODE_BUILD_TOOLS "Build Polycode tools" ON)

# Download and build all dependencies on Windows and Mac
IF(APPLE OR WIN32)
	SET(common_externals ON)
ELSE()
	SET(common_externals OFF)
ENDIF()

# Options for what components should be downloaded and built
OPTION(POLYCODE_EXTERNAL_PHYSFS "Download and build the PhysFS package" ${common_externals})
#OPTION(OpenGL REQUIRED)
OPTION(POLYCODE_EXTERNAL_OPENAL "Download and build the OpenAL package" ${common_externals})
OPTION(POLYCODE_EXTERNAL_FREETYPE "Download and build the Freetype2 package" ${common_externals})
OPTION(POLYCODE_EXTERNAL_PNG "Download and build the PNG package" ${common_externals})
OPTION(POLYCODE_EXTERNAL_VORBISFILE "Download and build the Vorbis File package" ${common_externals})

OPTION(POLYCODE_BUILD_BOX2D "Download and build the Box2D package" ON)
OPTION(POLYCODE_BUILD_BULLET "Download and build the Bullet package" ON)
OPTION(POLYCODE_BUILD_ASSIMP "Download and build the Assimp package" ON)

OPTION(POLYCODE_INSTALL_FRAMEWORK "Install Polycode Core, Modules and Tools" ON)

# Some non-standard CMake modules
SET(CMAKE_MODULE_PATH ${PolyCode_SOURCE_DIR}/Build/CMakeModules)

IF(WIN32)
    SET(CMAKE_PREFIX_PATH ${PolyCode_SOURCE_DIR}/Release/Win/Framework/Dependencies)
    SET(CMAKE_SYSTEM_LIBRARY_PATH ${CMAKE_PREFIX_PATH}/Lib/Release)
ENDIF(WIN32)

# Process subdirectories
ADD_SUBDIRECTORY(Core)

IF(POLYCODE_BUILD_BINDINGS)
    FIND_PACKAGE(Lua51 REQUIRED)
    ADD_SUBDIRECTORY(Bindings/Contents)
ENDIF(POLYCODE_BUILD_BINDINGS)

IF(POLYCODE_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(Examples/C++)
ENDIF(POLYCODE_BUILD_EXAMPLES)

IF(POLYCODE_BUILD_MODULES)
    ADD_SUBDIRECTORY(Modules)
ENDIF(POLYCODE_BUILD_MODULES)

IF(POLYCODE_BUILD_PLAYER)
    FIND_PACKAGE(Lua51 REQUIRED)
    ADD_SUBDIRECTORY(Player/Contents)
ENDIF(POLYCODE_BUILD_PLAYER)

IF(POLYCODE_BUILD_TOOLS)
    ADD_SUBDIRECTORY(Tools)
ENDIF(POLYCODE_BUILD_TOOLS)

# Install assets and dependencies
