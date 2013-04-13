INCLUDE(ExternalProject)

SET(box2d_PREFIX ${PROJECT_BINARY_DIR}/box2d)

# Needs fpic to link in shared lib on Linux
#IF(CMAKE_COMPILER_IS_GNUCXX)
#    SET(box2d_CXX_ARGS -DCMAKE_CXX_FLAGS=-fPIC)
#ENDIF(CMAKE_COMPILER_IS_GNUCXX)

SET(box2d_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_DEBUG_POSTFIX=_d 
    -DBOX2D_INSTALL=ON 
    -DBOX2D_BUILD_EXAMPLES=OFF 
    ${box2d_CXX_ARGS}
)

ExternalProject_Add(box2d
    PREFIX ${box2d_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://box2d.googlecode.com/files/Box2D_v2.1.2.zip
    URL_MD5 59d142cd8d4d73e8832c7b67591f590c

    # Box2D's source isn't in the top level directory so add a dummy file to set cmake right
    PATCH_COMMAND ${CMAKE_COMMAND} -E echo ADD_SUBDIRECTORY(Box2D) > <SOURCE_DIR>/CMakeLists.txt
    
    INSTALL_DIR ${POLYCODE_DEPS_MODULES_PREFIX}
    CMAKE_ARGS ${box2d_CMAKE_ARGS}
)
