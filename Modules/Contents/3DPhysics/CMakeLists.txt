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
    ../../Dependencies/Include/Bullet
    Include
)

#ADD_LIBRARY(Polycode3DPhysics SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
ADD_LIBRARY(Polycode3DPhysicsStatic ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})

