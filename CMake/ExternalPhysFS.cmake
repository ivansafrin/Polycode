# Build a local version
INCLUDE(ExternalProject)

SET(physfs_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/physfs)

SET(physfs_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_DEBUG_POSTFIX=d
    -DPHYSFS_BUILD_TEST=FALSE
    -DPHYSFS_BUILD_SHARED=FALSE
    -DPHYSFS_BUILD_WX_TEST=FALSE
)

ExternalProject_Add(physfs
    PREFIX ${physfs_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://offload1.icculus.org:9090/physfs/downloads/physfs-2.0.2.tar.gz
    URL_MD5 4e8927c3d30279b03e2592106eb9184a

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/physfs.cmake <SOURCE_DIR>/CMakeLists.txt

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${physfs_CMAKE_ARGS}
)

