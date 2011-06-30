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

ADD_LIBRARY(PolycodeLua SHARED ${polycodeLua_SRCS} ${polycodeLua_HDRS})
ADD_LIBRARY(PolycodeLuaStatic ${polycodeLua_SRCS} ${polycodeLua_HDRS})

