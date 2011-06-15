INCLUDE(PolycodeIncludes)

SET(polycode3DPhysics_SRCS
    Source/PolyPhysicsSceneEntity.cpp
    Source/PolyPhysicsScene.cpp
    Source/PolyCollisionSceneEntity.cpp
    Source/PolyCollisionScene.cpp
)

SET(polycode3DPhysics_HDRS
    Include/PolyPhysicsSceneEntity.h
    Include/Polycode3DPhysics.h
    Include/PolyCollisionScene.h
    Include/PolyPhysicsScene.h
    Include/PolyCollisionSceneEntity.h
)

INCLUDE_DIRECTORIES(
    ${BULLET_INCLUDE_DIR}
    Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

#IF(POLYCODE_BUILD_SHARED)
ADD_LIBRARY(Polycode3DPhysics ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
TARGET_LINK_LIBRARIES(Polycode3DPhysics 
    Polycore
    ${BULLET_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${VORBISFILE_LIBRARY})
IF(APPLE)
    TARGET_LINK_LIBRARIES(Polycode3DPhysics "-framework Cocoa")
ENDIF(APPLE)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
#    ADD_LIBRARY(Polycode3DPhysics_static ${polycode3DPhysics_SRCS} ${polycode3DPhysics_HDRS})
#    TARGET_LINK_LIBRARIES(Polycode3DPhysics_static Polycore_static)
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    # install headers
    INSTALL(FILES ${polycode3DPhysics_HDRS} 
        DESTINATION Modules/include)

     # install libraries
#    IF(POLYCODE_BUILD_SHARED)
     INSTALL(TARGETS Polycode3DPhysics 
         DESTINATION Modules/lib)
#    ENDIF()
#    IF(POLYCODE_BUILD_STATIC)
#        INSTALL(TARGETS Polycode3DPhysics_static 
#            DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF()
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
