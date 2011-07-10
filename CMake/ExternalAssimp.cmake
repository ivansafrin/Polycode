# Build a local version
INCLUDE(ExternalProject)

SET(assimp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/assimp)

ExternalProject_Add(assimp
    PREFIX ${assimp_PREFIX}
    URL http://download.sourceforge.net/assimp/assimp--2.0.863-sdk.zip
    URL_MD5 9f41662501bd9d9533c4cf03b7c25d5b
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DENABLE_BOOST_WORKAROUND=ON -DBUILD_ASSIMP_TOOLS=OFF -DBUILD_TESTS=OFF
)

# install built files
ExternalProject_Get_Property(assimp install_dir)

INSTALL(DIRECTORY ${install_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}
    FILES_MATCHING PATTERN "*.h")
#INSTALL(DIRECTORY ${install_dir}/bin
#    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}/bin)
INSTALL(DIRECTORY ${install_dir}/lib
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}/lib)
