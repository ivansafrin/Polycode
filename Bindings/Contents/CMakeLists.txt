SET(polycodeLua_SRCS
    LUA/Source/PolycodeLUA.cpp
)

SET(polycodeLua_HDRS
    LUA/Include/PolycodeLUAWrappers.h
    LUA/Include/PolycodeLUA.h
    LUA/Include/PolycodeLUA2D.h
)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    LUA/Include
)

IF(POLYCODE_BUILD_SHARED)
    LINK_LIBRARIES(Polycore)
    ADD_LIBRARY(PolycodeLua SHARED ${polycodeLua_SRCS} ${polycodeLua_HDRS})
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    LINK_LIBRARIES(Polycore_static)
    ADD_LIBRARY(PolycodeLua_static ${polycodeLua_SRCS} ${polycodeLua_HDRS})
ENDIF(POLYCODE_BUILD_STATIC)

