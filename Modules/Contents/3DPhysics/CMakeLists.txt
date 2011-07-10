INCLUDE(PolycodeIncludes)

SET(polycode3DPhysics_SRCS
    Source/PolyPhysicsSceneEntity.cpp
    Source/PolyPhysicsScene.cpp
    Source/PolyCollisionSceneEntity.cpp
    Source/PolyCollisionScene.cpp
)

SET(polycode3DPhysics_HDRS
    Include/PolyPhysicsSceneEntity.h
    Include/Polycode3DPhysics.h
    Include/PolyCollisionScene.h
    Include/PolyPhysicsScene.h
    Include/PolyCollisionSceneEntity.h
)

INCLUDE_DIRECTORIES(
    ${BULLET_INCLUDE_DIRS}
    Include
)

IF(POLYCODE_BUILD_SHARED)
	LINK_LIBRARIES(${BULLET_LIBRARIES})
	ADD_LIBRARY(Polycode3DPhysics SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
	TARGET_LINK_LIBRARIES(Polycode3DPhysics PolyCore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_LIBRARY(Polycode3DPhysics_static ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
	TARGET_LINK_LIBRARIES(Polycode3DPhysics_static PolyCore_static)
ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    # install headers
    INSTALL(FILES ${polycode3DPhysics_HDRS} DESTINATION Framework/Modules/Include)

    # install libraries
    IF(POLYCODE_BUILD_SHARED)
        INSTALL(TARGETS Polycode3DPhysics DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF()
    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS Polycode3DPhysics_static DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF()
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
