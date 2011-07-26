CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Polycode)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
    MESSAGE("No CMAKE_BUILD_TYPE specified, defaulting to ${CMAKE_BUILD_TYPE}")
ENDIF(NOT CMAKE_BUILD_TYPE)

#IF(APPLE OR WIN32)
#    SET(build_player OFF)
#ELSE()
#    SET(build_player OFF)
#ENDIF()

# Options for what components to build
#OPTION(POLYCODE_BUILD_SHARED "Build Polycode shared libraries" OFF)
#OPTION(POLYCODE_BUILD_STATIC "Build Polycode static libraries" ON)
OPTION(POLYCODE_BUILD_BINDINGS "Build Polycode Lua bindings" OFF)
OPTION(POLYCODE_BUILD_EXAMPLES "Build Polycode examples" ON)
OPTION(POLYCODE_BUILD_MODULES "Build Polycode modules" ON)
OPTION(POLYCODE_BUILD_PLAYER "Build Polycode standalone player" OFF)
OPTION(POLYCODE_BUILD_TOOLS "Build Polycode tools" ON)

OPTION(POLYCODE_INSTALL_FRAMEWORK "Install Polycode Core, Modules and Tools" ON)
OPTION(POLYCODE_INSTALL_PLAYER "Install Polycode Player" ${POLYCODE_BUILD_PLAYER})

# Some non-standard CMake modules
SET(CMAKE_MODULE_PATH ${Polycode_SOURCE_DIR}/CMake)

IF(NOT POLYCODE_RELEASE_DIR)
    SET(POLYCODE_RELEASE_DIR ${Polycode_SOURCE_DIR}/Release/${CMAKE_SYSTEM_NAME})
    MESSAGE("No POLYCODE_RELEASE_DIR specified, to ${POLYCODE_RELEASE_DIR}") 
ENDIF(NOT POLYCODE_RELEASE_DIR)

# set default externals install location
SET(CMAKE_PREFIX_PATH 
    ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies
    ${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies
    ${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies)

MESSAGE(DEBUG "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")

# Process subdirectories
ADD_SUBDIRECTORY(Core/Contents)
ADD_SUBDIRECTORY("Assets/Default asset pack")

IF(POLYCODE_BUILD_BINDINGS)
    ADD_SUBDIRECTORY(Bindings)
ENDIF(POLYCODE_BUILD_BINDINGS)

IF(POLYCODE_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(Examples/C++)
ENDIF(POLYCODE_BUILD_EXAMPLES)

IF(POLYCODE_BUILD_MODULES)
    ADD_SUBDIRECTORY(Modules/Contents)
ENDIF(POLYCODE_BUILD_MODULES)

IF(POLYCODE_BUILD_PLAYER)
    ADD_SUBDIRECTORY(Player/Contents)
ENDIF(POLYCODE_BUILD_PLAYER)

IF(POLYCODE_BUILD_TOOLS)
    ADD_SUBDIRECTORY(Tools/Contents)
ENDIF(POLYCODE_BUILD_TOOLS)

# Install assets and dependencies
