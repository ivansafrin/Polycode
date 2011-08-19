INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Lua51 REQUIRED)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${BULLET_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include
    Include
)

SET(polycode3DPhysics_SRCS
    Source/Physics3DLUA.cpp
)

SET(polycode3DPhysics_HDRS
    Include/Physics3DLUA.h
    Include/Physics3DLUAWrappers.h
)

ADD_LIBRARY(Physics3D SHARED ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
TARGET_LINK_LIBRARIES(Physics3D
    Polycore
    Polycode3DPhysics
    ${BULLET_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${VORBISFILE_LIBRARY}
    ${LUA_LIBRARY})
IF(APPLE)
    TARGET_LINK_LIBRARIES(Physics3D "-framework Cocoa")
    TARGET_LINK_LIBRARIES(Physics3D "-framework IOKit")
ENDIF(APPLE)

SET(CMAKE_DEBUG_POSTFIX "_d")

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
