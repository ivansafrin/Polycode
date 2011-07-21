# Build a local version of libogg, libvorbis and libvorbisfile
INCLUDE(ExternalProject)

SET(oggvorbis_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/oggvorbis)

SET(oggvorbis_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)

EXTERNALPROJECT_ADD(libogg
    PREFIX ${oggvorbis_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://downloads.xiph.org/releases/ogg/libogg-1.2.2.tar.gz
    URL_MD5 5a9fcabc9a1b7c6f1cd75ddc78f36c56

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/libogg.cmake <SOURCE_DIR>/CMakeLists.txt

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${oggvorbis_CMAKE_ARGS}
)

ExternalProject_Get_Property(libogg install_dir)

EXTERNALPROJECT_ADD(libvorbis
    DEPENDS libogg
    PREFIX ${oggvorbis_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.2.tar.gz
    URL_MD5 c870b9bd5858a0ecb5275c14486d9554

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/libvorbis.cmake <SOURCE_DIR>/CMakeLists.txt

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${oggvorbis_CMAKE_ARGS} -DCMAKE_PREFIX_PATH=${install_dir} # to find libogg
)
