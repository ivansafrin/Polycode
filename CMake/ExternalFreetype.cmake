# Build a local version of freetype
INCLUDE(ExternalProject)

SET(freetype_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freetype)

SET(freetype_CMAKE_ARGS
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> 
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
)

EXTERNALPROJECT_ADD(freetype
    PREFIX ${freetype_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://download.savannah.gnu.org/releases/freetype/freetype-2.6.tar.gz
    URL_MD5 1d733ea6c1b7b3df38169fbdbec47d2b

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/freetype/ftoption.h <SOURCE_DIR>/include/config/ftoption.h

    INSTALL_DIR ${POLYCODE_DEPS_CORE_PREFIX}
    CMAKE_ARGS ${freetype_CMAKE_ARGS}
)
