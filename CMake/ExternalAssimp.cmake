# Build a local version
INCLUDE(ExternalProject)

SET(assimp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/assimp)

SET(assimp_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_DEBUG_POSTFIX=d 
    -DENABLE_BOOST_WORKAROUND=ON 
    -DBUILD_ASSIMP_TOOLS=OFF 
    -DBUILD_TESTS=OFF
)

IF(APPLE)
LIST(APPEND assimp_CMAKE_ARGS -DCMAKE_CXX_FLAGS_RELEASE="-O2")
ENDIF(APPLE)

ExternalProject_Add(assimp
    PREFIX ${assimp_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp.cmake <SOURCE_DIR>/code/CMakeLists.txt

    URL http://download.sourceforge.net/assimp/assimp--2.0.863-sdk.zip
    URL_MD5 9f41662501bd9d9533c4cf03b7c25d5b

    INSTALL_DIR ${POLYCODE_DEPS_TOOLS_PREFIX} 
    CMAKE_ARGS ${assimp_CMAKE_ARGS}
)
