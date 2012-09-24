CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8) # 2.8.5 needed for full URL support, 2.8.8 now needed for new Xcode support

PROJECT(PolycodeDependencies)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
    MESSAGE("No CMAKE_BUILD_TYPE specified, defaulting to ${CMAKE_BUILD_TYPE}") 
ENDIF(NOT CMAKE_BUILD_TYPE)


IF(NOT POLYCODE_RELEASE_DIR)
    SET(POLYCODE_RELEASE_DIR ${PolycodeDependencies_SOURCE_DIR}/../Release/${CMAKE_SYSTEM_NAME}
        CACHE PATH "Choose the root directory that the Polycode release will be installed in.")
    MESSAGE("No POLYCODE_RELEASE_DIR specified, to ${POLYCODE_RELEASE_DIR}") 
ENDIF(NOT POLYCODE_RELEASE_DIR)

IF(NOT POLYCODE_DEPS_DOWNLOAD_DIR)
    SET(POLYCODE_DEPS_DOWNLOAD_DIR ${PolycodeDependencies_SOURCE_DIR}/Downloads)
    MESSAGE("No POLYCODE_DEPS_DOWNLOAD_DIR specified, to ${POLYCODE_DEPS_DOWNLOAD_DIR}") 
ENDIF(NOT POLYCODE_DEPS_DOWNLOAD_DIR)

# Install directories
SET(POLYCODE_DEPS_CORE_PREFIX ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies)
SET(POLYCODE_DEPS_MODULES_PREFIX ${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies)
SET(POLYCODE_DEPS_TOOLS_PREFIX ${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies)

# Some non-standard CMake modules
SET(CMAKE_MODULE_PATH ${PolycodeDependencies_SOURCE_DIR}/../CMake)

# Download and build all dependencies on Windows and Mac, for Linux recommend using prebuilt packages
#IF(APPLE OR WIN32)
    SET(common_deps ON)
#ELSE()
#    SET(common_deps OFF)
#ENDIF()

# Options for what components should be downloaded and built

# glext.h is sometimes missing
FIND_PATH(GLEXT_INCLUDE_DIR GL/glext.h)
IF(GLEXT_INCLUDE_DIR)
    SET(internal_GLEXT OFF)
ELSE(GLEXT_INCLUDE_DIR)
    SET(internal_GLEXT ${common_deps})
ENDIF(GLEXT_INCLUDE_DIR)

IF(MSVC)
    # wglext.h is needed on windows
    FIND_PATH(WGLEXT_INCLUDE_DIR GL/wglext.h)
    IF(WGLEXT_INCLUDE_DIR)
        SET(internal_WGLEXT OFF)
    ELSE(GLEXT_INCLUDE_DIR)
        SET(internal_WGLEXT ${common_deps})
    ENDIF(WGLEXT_INCLUDE_DIR)
ELSE(MSVC)
    SET(internal_WGLEXT OFF)
ENDIF(MSVC)

#FIND_PACKAGE(PhysFS)
#IF(PHYSFS_FOUND)
#    SET(internal_PHYSFS OFF)
#ELSE(PHYSFS_FOUND)
    SET(internal_PHYSFS ON)
#ENDIF(PHYSFS_FOUND)

IF(APPLE)
FIND_PACKAGE(OpenAL)
IF(OPENAL_FOUND)
    SET(internal_OPENAL OFF)
ELSE(OPENAL_FOUND)
    SET(internal_OPENAL ON)
ENDIF(OPENAL_FOUND)
ELSE()
    SET(internal_OPENAL ON)
ENDIF(APPLE)

#FIND_PACKAGE(Freetype)
#IF(FREETYPE_FOUND)
#    SET(internal_FREETYPE OFF)
#ELSE(FREETYPE_FOUND)
    SET(internal_FREETYPE ON)
#ENDIF(FREETYPE_FOUND)

#FIND_PACKAGE(PNG)
#IF(PNG_FOUND)
#    SET(internal_PNG OFF)
#ELSE(PNG_FOUND)
    SET(internal_PNG ON)
#ENDIF(PNG_FOUND)

#FIND_PACKAGE(VorbisFile)
#IF(VORBISFILE_FOUND)
#    SET(internal_VORBISFILE OFF)
#ELSE(VORBISFILE_FOUND)
    SET(internal_VORBISFILE ON)
#ENDIF(VORBISFILE_FOUND)

#FIND_PACKAGE(Lua51)
#IF(LUA51_FOUND)
#    SET(internal_LUA OFF)
#ELSE(LUA51_FOUND)
    SET(internal_LUA ON)
#ENDIF(LUA51_FOUND)

#FIND_PACKAGE(Box2D)
#IF(BOX2D_FOUND)
#    SET(internal_BOX2D OFF)
#ELSE(BOX2D_FOUND)
    SET(internal_BOX2D ON)
#ENDIF(BOX2D_FOUND)

#FIND_PACKAGE(Bullet)
#IF(BULLET_FOUND)
#    SET(internal_BULLET OFF)
#ELSE(BULLET_FOUND)
    SET(internal_BULLET ON)
#ENDIF(BULLET_FOUND)

IF(POLYCODE_BUILD_TOOLS)
#FIND_PACKAGE(Assimp)
#IF(ASSIMP_FOUND)
#    SET(internal_ASSIMP OFF)
#ELSE(ASSIMP_FOUND)
    SET(internal_ASSIMP ON)
#ENDIF(ASSIMP_FOUND)
ENDIF(POLYCODE_BUILD_TOOLS)

OPTION(POLYCODE_DEPS_GLEXT "Download GL/glext.h header" ${internal_GLEXT})
OPTION(POLYCODE_DEPS_WGLEXT "Download GL/wglext.h header" ${internal_WGLEXT})

OPTION(POLYCODE_DEPS_PHYSFS "Download and build the PhysFS package" ${internal_PHYSFS})
OPTION(POLYCODE_DEPS_OPENAL "Download and build the OpenAL package" ${internal_OPENAL})
OPTION(POLYCODE_DEPS_FREETYPE "Download and build the Freetype2 package" ${internal_FREETYPE})
OPTION(POLYCODE_DEPS_PNG "Download and build the PNG package" ${internal_PNG})
OPTION(POLYCODE_DEPS_OGGVORBIS "Download and build the Ogg Vorbis packages" ${internal_VORBISFILE})

OPTION(POLYCODE_DEPS_LUA51 "Download and build the Lua51 package" ${internal_LUA})
OPTION(POLYCODE_DEPS_BOX2D "Download and build the Box2D package" ${internal_BOX2D})
OPTION(POLYCODE_DEPS_BULLET "Download and build the Bullet package" ${internal_BULLET})
OPTION(POLYCODE_DEPS_ASSIMP "Download and build the Assimp package" ${internal_ASSIMP})

IF(POLYCODE_DEPS_PNG)
    INCLUDE(ExternalPNG)
ENDIF(POLYCODE_DEPS_PNG)

IF(POLYCODE_DEPS_PHYSFS)
    INCLUDE(ExternalPhysFS)
ENDIF(POLYCODE_DEPS_PHYSFS)

IF(POLYCODE_DEPS_OPENAL)
    INCLUDE(ExternalOpenAL)
ENDIF(POLYCODE_DEPS_OPENAL)

IF(POLYCODE_DEPS_FREETYPE)
    INCLUDE(ExternalFreetype)
ENDIF(POLYCODE_DEPS_FREETYPE)

IF(POLYCODE_DEPS_OGGVORBIS)
    INCLUDE(ExternalOggVorbis)
ENDIF(POLYCODE_DEPS_OGGVORBIS)

IF(POLYCODE_DEPS_LUA51)
    INCLUDE(ExternalLua51)
ENDIF(POLYCODE_DEPS_LUA51)

IF(POLYCODE_DEPS_BOX2D)
    INCLUDE(ExternalBox2D)
ENDIF(POLYCODE_DEPS_BOX2D)

IF(POLYCODE_DEPS_BULLET)
    INCLUDE(ExternalBullet)
ENDIF(POLYCODE_DEPS_BULLET)

IF(POLYCODE_DEPS_ASSIMP AND POLYCODE_BUILD_TOOLS)
    INCLUDE(ExternalAssimp)
ENDIF(POLYCODE_DEPS_ASSIMP AND POLYCODE_BUILD_TOOLS)

# Use SDL on non-Apple unixes
#IF(UNIX AND NOT APPLE)
#    FIND_PACKAGE(SDL REQUIRED)
#ENDIF(UNIX AND NOT APPLE)

# Get missing GL headers for Windows
IF(POLYCODE_DEPS_GLEXT)
    INCLUDE(ExternalGLExt)
ENDIF(POLYCODE_DEPS_GLEXT)

IF(POLYCODE_DEPS_WGLEXT)
    INCLUDE(ExternalWGLExt)
ENDIF(POLYCODE_DEPS_WGLEXT)
