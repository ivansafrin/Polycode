INCLUDE(PolycodeIncludes)

SET(polycode2DPhysics_SRCS
    Source/Physics2DLUA.cpp
)

SET(polycode2DPhysics_HDRS
    Include/Physics2DLUA.h
    Include/Physics2DLUAWrappers.h
)

ADD_LIBRARY(Physics2D SHARED ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
