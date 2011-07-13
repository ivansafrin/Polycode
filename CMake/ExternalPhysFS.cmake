# Build a local version
INCLUDE(ExternalProject)

SET(physfs_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/physfs)

SET(physfs_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_DEBUG_POSTFIX=d
)

ExternalProject_Add(physfs
    PREFIX ${physfs_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://offload1.icculus.org:9090/physfs/downloads/physfs-2.0.2.tar.gz
    URL_MD5 4e8927c3d30279b03e2592106eb9184a

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${physfs_CMAKE_ARGS}
)



