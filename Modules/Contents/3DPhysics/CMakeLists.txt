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

#ADD_LIBRARY(Polycode3DPhysics SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
ADD_LIBRARY(Polycode3DPhysicsStatic ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})

IF(POLYCODE_BUILD_SHARED)
LINK_LIBRARIES(${BULLET_LIBRARIES})
ADD_LIBRARY(Polycode3DPhysics SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
TARGET_LINK_LIBRARIES(Polycode3DPhysics PolyCore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
ADD_LIBRARY(Polycode3DPhysics_static ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
TARGET_LINK_LIBRARIES(Polycode3DPhysics_static PolyCore_static)
ENDIF(POLYCODE_BUILD_STATIC)
