INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Lua51 REQUIRED)
FIND_PACKAGE(Bullet REQUIRED)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${BULLET_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include
    Include
    ../../Contents/3DPhysics/Include
)

SET(polycode3DPhysics_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Physics3DLUA.cpp
    ../../Contents/3DPhysics/Source/PolyPhysicsSceneEntity.cpp
    ../../Contents/3DPhysics/Source/PolyPhysicsScene.cpp
    ../../Contents/3DPhysics/Source/PolyCollisionSceneEntity.cpp
    ../../Contents/3DPhysics/Source/PolyCollisionScene.cpp
)

SET(polycode3DPhysics_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics3DLUA.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/Physics3DLUAWrappers.h
    ../../Contents/3DPhysics/Include/PolyPhysicsSceneEntity.h
    ../../Contents/3DPhysics/Include/Polycode3DPhysics.h
    ../../Contents/3DPhysics/Include/PolyCollisionScene.h
    ../../Contents/3DPhysics/Include/PolyPhysicsScene.h
    ../../Contents/3DPhysics/Include/PolyCollisionSceneEntity.h
)

ADD_LIBRARY(Physics3D SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})

SET_SOURCE_FILES_PROPERTIES(Source/Physics3DLUA.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics3DLUAWrappers.h PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/Physics3DLUA.h PROPERTIES GENERATED 1)
ADD_DEPENDENCIES(Physics2D PolycodeLuaGenerate)

SET(CMAKE_DEBUG_POSTFIX "_d")

SET_TARGET_PROPERTIES(Physics3D PROPERTIES PREFIX "")

IF(APPLE)
TARGET_LINK_LIBRARIES(Physics3D
	Polycore
	${LUA_LIBRARY}
	${BULLET_LIBRARIES}
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
TARGET_LINK_LIBRARIES(Physics3D
	Polycore
	${LUA_LIBRARY}
	${BULLET_LIBRARIES}
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
    INSTALL(FILES ${polycode3DPhysics_HDRS} 
        DESTINATION Bindings/Lua/Modules/3DPhysics/include)

    INSTALL(DIRECTORY API DESTINATION Bindings/Lua/Modules/3DPhysics)
	
    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS PolycodeLua_dynamic
#            DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
     INSTALL(TARGETS Physics3D
         DESTINATION Bindings/Lua/Modules/3DPhysics/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
