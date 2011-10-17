INCLUDE(PolycodeIncludes)

SET(polycodeKinect_SRCS
    Source/PolycodeKinect.cpp
)

SET(polycodeKinect_HDRS
    Include/PolycodeKinect.h
)

INCLUDE_DIRECTORIES(
    ${FREENECT_INCLUDE_DIR}
    Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

#IF(POLYCODE_BUILD_SHARED)
#ADD_LIBRARY(PolycodeKinect SHARED ${polycodeKinect_SRCS} ${polycodeKinect_HDRS})
#TARGET_LINK_LIBRARIES(PolycodeKinect ${BOX2D_LIBRARIES})
#IF(APPLE)
#    TARGET_LINK_LIBRARIES(PolycodeKinect
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
ADD_LIBRARY(PolycodeKinect ${polycodeKinect_SRCS} ${polycodeKinect_HDRS})
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeKinect_HDRS} DESTINATION Modules/include)

    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
    INSTALL(TARGETS PolycodeKinect EXPORT PolycodeKinect-targets DESTINATION Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
#    IF(POLYCODE_BUILD_STATIC)
#        INSTALL(TARGETS PolycodeKinect_static DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)

    INSTALL(EXPORT PolycodeKinect-targets DESTINATION
        Modules/lib/PolycodeKinect)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)
