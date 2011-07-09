IF(POLYCODE_BUILD_BOX2D)
    
    INCLUDE(ExternalProject)

    SET(box2d_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Box2D)
    
    # Needs fpic to link in shared lib on Linux
    IF(CMAKE_COMPILER_IS_GNUCXX)
        SET(box2d_CXX_ARGS -DCMAKE_CXX_FLAGS=-fPIC)
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)
    
    ExternalProject_Add(box2d
        PREFIX ${box2d_PREFIX}
        
        URL http://box2d.googlecode.com/files/Box2D_v2.1.2.zip
        URL_MD5 59d142cd8d4d73e8832c7b67591f590c

        # Box2D's source isn't in the top level directory so add a dummy file to set cmake right
        PATCH_COMMAND cmake -E echo ADD_SUBDIRECTORY(Box2D) > <SOURCE_DIR>/CMakeLists.txt
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DBOX2D_BUILD_EXAMPLES=OFF ${box2d_CXX_ARGS}
    )
    
    SET(CMAKE_PREFIX_PATH ${box2d_PREFIX})
ENDIF(POLYCODE_BUILD_BOX2D)

FIND_PACKAGE(Box2D)

ADD_SUBDIRECTORY(Contents)
