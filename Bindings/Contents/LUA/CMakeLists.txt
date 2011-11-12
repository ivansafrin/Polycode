INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Lua REQUIRED)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    Include
)

SET(polycodeLua_SRCS
    Source/PolycodeLUA.cpp
)

SET(polycodeLua_HDRS
    Include/PolycodeLUAWrappers.h
    Include/PolycodeLUA.h
)

SET(CMAKE_DEBUG_POSTFIX "_d")

#IF(POLYCODE_BUILD_SHARED)
#    ADD_LIBRARY(PolycodeLua SHARED ${polycodeLua_SRCS} ${polycodeLua_HDRS})
#    TARGET_LINK_LIBRARIES(PolycodeLua Polycore ${LUA_LIBRARY})
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_LIBRARY(PolycodeLua ${polycodeLua_SRCS} ${polycodeLua_HDRS})
ADD_DEPENDENCIES(PolycodeLua PolycodeLuaGenerate)
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeLua_HDRS} 
        DESTINATION Bindings/Lua/Core/include)

    INSTALL(DIRECTORY API DESTINATION Bindings/Lua/Core)
	
    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS PolycodeLua_dynamic
#            DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
     INSTALL(TARGETS PolycodeLua 
         DESTINATION Bindings/Lua/Core/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
