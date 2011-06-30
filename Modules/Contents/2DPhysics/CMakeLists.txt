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
    Include
)

ADD_LIBRARY(Polycode2DPhysics SHARED ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
ADD_LIBRARY(Polycode2DPhysicsStatic ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})

