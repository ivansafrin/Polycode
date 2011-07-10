INCLUDE(ExternalProject)

SET(bullet_PREFIX ${PROJECT_BINARY_DIR}/bullet)

SET(bullet_CMAKE_ARGS 
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DINSTALL_LIBS=ON
    -DBUILD_DEMOS=OFF
    -DBUILD_EXTRAS=OFF
    -DBUILD_UNIT_TESTS=OFF
)

IF(CMAKE_COMPILER_IS_GNUCXX)
    # Needs fpic to link in shared lib on Linux with GCC
    LIST(APPEND bullet_CMAKE_ARGS -DCMAKE_CXX_FLAGS=-fPIC)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

ExternalProject_Add(bullet
    PREFIX ${bullet_PREFIX}
    
    URL http://bullet.googlecode.com/files/bullet-2.78.zip
    URL_MD5 99d4070864c9f73521481ba9cda25038

    CMAKE_ARGS ${bullet_CMAKE_ARGS}
)

ExternalProject_Get_Property(bullet install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}
    FILES_MATCHING PATTERN "*.h")
#INSTALL(DIRECTORY ${install_dir}/bin
#    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX})
INSTALL(DIRECTORY ${install_dir}/lib
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX})
