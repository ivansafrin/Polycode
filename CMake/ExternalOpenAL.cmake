# Build a local version
INCLUDE(ExternalProject)

SET(openal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/openal)

SET(openal_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_DEBUG_POSTFIX=d
)

ExternalProject_Add(openal
    PREFIX ${openal_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://kcat.strangesoft.net/openal-releases/openal-soft-1.14.tar.bz2
    URL_MD5 3d8b86c21a2f87a2a5e60f78f3b3f03d
    
    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${openal_CMAKE_ARGS}
)
