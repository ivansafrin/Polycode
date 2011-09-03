INCLUDE(PolycodeIncludes)

SET(polycode2DPhysics_SRCS
    Source/PolyPhysicsScreen.cpp
    Source/PolyPhysicsScreenEntity.cpp
)

SET(polycode2DPhysics_HDRS
    Include/Polycode2DPhysics.h
    Include/PolyPhysicsScreenEntity.h
    Include/PolyPhysicsScreen.h
)

INCLUDE_DIRECTORIES(
    ${BOX2D_INCLUDE_DIRS}
    Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

#IF(POLYCODE_BUILD_SHARED)
#ADD_LIBRARY(Polycode2DPhysics SHARED ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
#TARGET_LINK_LIBRARIES(Polycode2DPhysics ${BOX2D_LIBRARIES})
#IF(APPLE)
#    TARGET_LINK_LIBRARIES(Polycode2DPhysics
#        Polycore
#        ${OPENGL_LIBRARIES}
#        ${OPENAL_LIBRARY}
#        ${PNG_LIBRARIES}
#        ${FREETYPE_LIBRARIES}
#        ${PHYSFS_LIBRARY}
#        ${VORBISFILE_LIBRARY}
#        "-framework Cocoa")
#ENDIF(APPLE)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_LIBRARY(Polycode2DPhysics ${polycode2DPhysics_SRCS} ${polycode2DPhysics_HDRS})
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycode2DPhysics_HDRS} DESTINATION Modules/include)

    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
    INSTALL(TARGETS Polycode2DPhysics EXPORT Polycode2DPhysics-targets DESTINATION Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
#    IF(POLYCODE_BUILD_STATIC)
#        INSTALL(TARGETS Polycode2DPhysics_static DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)

    INSTALL(EXPORT Polycode2DPhysics-targets DESTINATION
        Modules/lib/Polycode2DPhysics)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
