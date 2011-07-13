# Build a local version
INCLUDE(ExternalProject)

SET(assimp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/assimp)

ExternalProject_Add(assimp
    PREFIX ${assimp_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://download.sourceforge.net/assimp/assimp--2.0.863-sdk.zip
    URL_MD5 9f41662501bd9d9533c4cf03b7c25d5b

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DENABLE_BOOST_WORKAROUND=ON -DBUILD_ASSIMP_TOOLS=OFF -DBUILD_TESTS=OFF
)

# install built files
ExternalProject_Get_Property(assimp install_dir)

# install includes
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_DEPS_TOOLS_PREFIX}/Include)

# install debug lib
INSTALL(FILES ${install_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_TOOLS_PREFIX}/Lib
    CONFIGURATIONS Debug
    RENAME assimpd${CMAKE_STATIC_LIBRARY_SUFFIX})

# install release lib
INSTALL(FILES ${install_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_TOOLS_PREFIX}/Lib
    CONFIGURATIONS Release)
