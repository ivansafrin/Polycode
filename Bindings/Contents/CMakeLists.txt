INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Lua51 REQUIRED)
INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    LUA/Include
)

SET(polycodeLua_SRCS
    LUA/Source/PolycodeLUA.cpp
)

SET(polycodeLua_HDRS
    LUA/Include/PolycodeLUAWrappers.h
    LUA/Include/PolycodeLUA.h
    LUA/Include/PolycodeLUA2D.h
)

SET(CMAKE_DEBUG_POSTFIX "_d")

#IF(POLYCODE_BUILD_SHARED)
#    ADD_LIBRARY(PolycodeLua SHARED ${polycodeLua_SRCS} ${polycodeLua_HDRS})
#    TARGET_LINK_LIBRARIES(PolycodeLua Polycore ${LUA_LIBRARY})
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
#    ADD_LIBRARY(PolycodeLua_static ${polycodeLua_SRCS} ${polycodeLua_HDRS})
#    TARGET_LINK_LIBRARIES(PolycodeLua_static Polycore_static)
#ENDIF(POLYCODE_BUILD_STATIC)

ADD_LIBRARY(PolycodeLua ${polycodeLua_SRCS} ${polycodeLua_HDRS})
TARGET_LINK_LIBRARIES(PolycodeLua)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeLua_HDRS} DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/Include)

    # install libraries
    IF(POLYCODE_BUILD_SHARED)
        INSTALL(TARGETS PolycodeLua DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/Lib)
    ENDIF(POLYCODE_BUILD_SHARED)
    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS PolycodeLua_static DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/Lib)
    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
