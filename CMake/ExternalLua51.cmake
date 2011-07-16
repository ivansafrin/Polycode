# Build a local version
INCLUDE(ExternalProject)

SET(lua51_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/lua51)

SET(lua51_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_DEBUG_POSTFIX=d
)

ExternalProject_Add(lua51
    PREFIX ${lua51_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://www.lua.org/ftp/lua-5.1.4.tar.gz
    URL_MD5 d0870f2de55d59c1c8419f36e8fac150

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/lua51.cmake <SOURCE_DIR>/CMakeLists.txt

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${lua51_CMAKE_ARGS}
)

