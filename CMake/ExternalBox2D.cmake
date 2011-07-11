INCLUDE(ExternalProject)

SET(box2d_PREFIX ${PROJECT_BINARY_DIR}/box2d)

# Needs fpic to link in shared lib on Linux
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(box2d_CXX_ARGS -DCMAKE_CXX_FLAGS=-fPIC)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

SET(box2d_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DBOX2D_INSTALL=ON 
    -DBOX2D_BUILD_EXAMPLES=OFF 
    ${box2d_CXX_ARGS}
)

ExternalProject_Add(box2d
    PREFIX ${box2d_PREFIX}
    
    URL http://box2d.googlecode.com/files/Box2D_v2.1.2.zip
    URL_MD5 59d142cd8d4d73e8832c7b67591f590c

    # Box2D's source isn't in the top level directory so add a dummy file to set cmake right
    PATCH_COMMAND cmake -E echo ADD_SUBDIRECTORY(Box2D) > <SOURCE_DIR>/CMakeLists.txt
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DBOX2D_INSTALL=ON -DBOX2D_BUILD_EXAMPLES=OFF ${box2d_CXX_ARGS}
)

ExternalProject_Get_Property(box2d install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")
    
# install debug lib
INSTALL(FILES ${install_dir}/lib/Box2D${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug
    RENAME Box2D_d${CMAKE_STATIC_LIBRARY_SUFFIX})

# install release lib
INSTALL(FILES ${install_dir}/lib/Box2D${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_EXTERNALS_MODULES_PREFIX}/Lib/Release
    CONFIGURATIONS Release)

