IF(POLYCODE_BUILD_BOX2D)
    
    INCLUDE(ExternalProject)

    SET(box2d_PREFIX ${PROJECT_BINARY_DIR}/Modules/Dependencies/Box2D)
    
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
    
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${box2d_PREFIX})
ENDIF(POLYCODE_BUILD_BOX2D)

FIND_PACKAGE(Box2D)

IF(POLYCODE_BUILD_BULLET)
    
    INCLUDE(ExternalProject)

    SET(bullet_PREFIX ${PROJECT_BINARY_DIR}/Modules/Dependencies/Bullet)
        
    # Needs fpic to link in shared lib on Linux
    IF(CMAKE_COMPILER_IS_GNUCXX)
        SET(bullet_CXX_ARGS -DCMAKE_CXX_FLAGS=-fPIC)
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)

    ExternalProject_Add(bullet
        PREFIX ${bullet_PREFIX}
        
        URL http://bullet.googlecode.com/files/bullet-2.78.zip
        URL_MD5 99d4070864c9f73521481ba9cda25038

        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DBUILD_CPU_DEMOS=OFF ${bullet_CXX_ARGS}
    )
    
    # cmake seems to have trouble finding the includes
    SET(BULLET_INCLUDE_DIR ${bullet_PREFIX}/include/bullet)
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${bullet_PREFIX})
ENDIF(POLYCODE_BUILD_BULLET)

FIND_PACKAGE(Bullet)

ADD_SUBDIRECTORY(Contents)
