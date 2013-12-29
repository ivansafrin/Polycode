INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Lua51 REQUIRED)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${BOX2D_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/2DPhysics/Include
    Include
    ../../Contents/2DPhysics/Include
)

SET(polycode2DPhysics_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Physics2DLUA.cpp
)

SET(polycode2DPhysics_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics2DLUA.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics2DLUAWrappers.h
)

SET(CMAKE_DEBUG_POSTFIX "_d")

ADD_LIBRARY(Physics2DLua ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})

SET_SOURCE_FILES_PROPERTIES(Source/Physics2DLUA.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics2DLUAWrappers.h PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics2DLUA.h PROPERTIES GENERATED 1)
ADD_DEPENDENCIES(Physics2DLua PolycodeLuaGenerate)

SET_TARGET_PROPERTIES(Physics2DLua PROPERTIES PREFIX "")

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycode2DPhysics_HDRS} 
        DESTINATION Bindings/Lua/Modules/2DPhysics/include)
	
IF(NOT APPLE)
    INSTALL(FILES API/Physics2D.pak DESTINATION Player)
ENDIF(NOT APPLE)

	INSTALL(DIRECTORY API DESTINATION Bindings/Lua/Modules/2DPhysics)
	INSTALL(TARGETS Physics2DLua DESTINATION Bindings/Lua/Modules/2DPhysics/lib)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
