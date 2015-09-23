# Build a local version
INCLUDE(ExternalProject)

SET(assimp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/assimp)

SET(assimp_CMAKE_ARGS
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_DEBUG_POSTFIX=d
    -DENABLE_BOOST_WORKAROUND=ON
    -DBUILD_ASSIMP_TOOLS=OFF
    -DBUILD_TESTS=OFF
)

IF(APPLE)
    # Work around a compiler crash building assimp on Mac
    STRING(REPLACE "-O3" "-O2" assimp_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
    LIST(APPEND assimp_CMAKE_ARGS -DCMAKE_CXX_FLAGS_RELEASE=${assimp_CXX_FLAGS})
ENDIF(APPLE)

ExternalProject_Add(assimp
    PREFIX ${assimp_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp.cmake <SOURCE_DIR>/code/CMakeLists.txt && ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp_patch/Vertex.h <SOURCE_DIR>/code/Vertex.h  && ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp_patch/BlenderModifier.cpp <SOURCE_DIR>/code/BlenderModifier.cpp  && ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp_patch/LWOAnimation.cpp <SOURCE_DIR>/code/LWOAnimation.cpp && ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/assimp_patch/AssimpPCH.h <SOURCE_DIR>/code/AssimpPCH.h

    URL http://download.sourceforge.net/assimp/assimp--2.0.863-sdk.zip
    URL_MD5 9f41662501bd9d9533c4cf03b7c25d5b

    INSTALL_DIR ${POLYCODE_DEPS_TOOLS_PREFIX}
    CMAKE_ARGS ${assimp_CMAKE_ARGS}
)
