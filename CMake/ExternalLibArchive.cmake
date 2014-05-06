# Build a local version
INCLUDE(ExternalProject)

SET(libarchive_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libarchive)

SET(libarchive_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DENABLE_ICONV=OFF
    -DENABLE_TAR=OFF
    -DENABLE_OPENSSL=OFF
    -DENABLE_TEST=OFF
    -DCMAKE_DEBUG_POSTFIX=d
)

ExternalProject_Add(libarchive
    PREFIX ${libarchive_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    
    URL http://www.libarchive.org/downloads/libarchive-3.1.2.tar.gz
    URL_MD5 efad5a503f66329bb9d2f4308b5de98a
    
    INSTALL_DIR ${POLYCODE_DEPS_TOOLS_PREFIX}
    CMAKE_ARGS ${libarchive_CMAKE_ARGS}
)
