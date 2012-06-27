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
    ../../Contents/2DPhysics/Source/PolyPhysicsScreen.cpp
    ../../Contents/2DPhysics/Source/PolyPhysicsScreenEntity.cpp
)

SET(polycode2DPhysics_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics2DLUA.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics2DLUAWrappers.h
    ../../Contents/2DPhysics/Include/Polycode2DPhysics.h
    ../../Contents/2DPhysics/Include/PolyPhysicsScreenEntity.h
    ../../Contents/2DPhysics/Include/PolyPhysicsScreen.h
)

ADD_LIBRARY(Physics2D SHARED ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})

SET_SOURCE_FILES_PROPERTIES(Source/Physics2DLUA.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics2DLUAWrappers.h PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics2DLUA.h PROPERTIES GENERATED 1)
ADD_DEPENDENCIES(Physics2D PolycodeLuaGenerate)

SET(CMAKE_DEBUG_POSTFIX "_d")

SET_TARGET_PROPERTIES(Physics2D PROPERTIES PREFIX "")

IF(APPLE)
TARGET_LINK_LIBRARIES(Physics2D
	Polycore
	${LUA_LIBRARY}
	${BOX2D_RELEASE_LIBRARY}
	"-framework Cocoa"
	"-framework IOKit"
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
	${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARIES}
        ${VORBIS_LIBRARIES}
        ${VORBISFILE_LIBRARIES}
        ${EXTRA_LIBS})
ELSE(APPLE)
TARGET_LINK_LIBRARIES(Physics2D
	Polycore
	${LUA_LIBRARY}
	${BOX2D_RELEASE_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARIES}
        ${VORBIS_LIBRARIES}
        ${VORBISFILE_LIBRARIES}
        ${EXTRA_LIBS})
ENDIF(APPLE)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycode2DPhysics_HDRS} 
        DESTINATION Bindings/Lua/Modules/2DPhysics/include)

    INSTALL(DIRECTORY API DESTINATION Bindings/Lua/Modules/2DPhysics)
	
    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS PolycodeLua_dynamic
#            DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
     INSTALL(TARGETS Physics2D
         DESTINATION Bindings/Lua/Modules/2DPhysics/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
