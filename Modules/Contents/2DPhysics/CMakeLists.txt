INCLUDE(PolycodeIncludes)

SET(polycode2DPhysics_SRCS
    Source/PolyPhysicsScreen.cpp
    Source/PolyPhysicsScreenEntity.cpp
)

SET(polycode2DPhysics_HDRS
    Include/Polycode2DPhysics.h
    Include/PolyPhysicsScreenEntity.h
    Include/PolyPhysicsScreen.h
)

INCLUDE_DIRECTORIES(
    ${BOX2D_INCLUDE_DIRS}
    Include
)

IF(POLYCODE_BUILD_SHARED)
    LINK_LIBRARIES(${BOX2D_LIBRARIES})
    ADD_LIBRARY(Polycode2DPhysics SHARED ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
    TARGET_LINK_LIBRARIES(Polycode2DPhysics PolyCore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    ADD_LIBRARY(Polycode2DPhysics_static ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
    TARGET_LINK_LIBRARIES(Polycode2DPhysics_static PolyCore_static)
ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycode2DPhysics_HDRS} DESTINATION Framework/Modules/Include)

    # install libraries
    IF(POLYCODE_BUILD_SHARED)
        INSTALL(TARGETS Polycode2DPhysics DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF(POLYCODE_BUILD_SHARED)
    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS Polycode2DPhysics_static DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
