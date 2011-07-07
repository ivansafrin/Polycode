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
    ADD_LIBRARY(PolycodeLua SHARED ${polycodeLua_SRCS} ${polycodeLua_HDRS})
    TARGET_LINK_LIBRARIES(PolycodeLua PolyCore ${LUA_LIBRARY})
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    ADD_LIBRARY(PolycodeLua_static ${polycodeLua_SRCS} ${polycodeLua_HDRS})
    TARGET_LINK_LIBRARIES(PolycodeLua_static PolyCore_static)
ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeLua_HDRS} DESTINATION Framework/Modules/Include)

    # install libraries
    IF(POLYCODE_BUILD_SHARED)
        INSTALL(TARGETS PolycodeLua DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF(POLYCODE_BUILD_SHARED)
    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS PolycodeLua_static DESTINATION Framework/Modules/Lib/${CMAKE_BUILD_TYPE})
    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
