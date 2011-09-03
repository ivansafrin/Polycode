INCLUDE(PolycodeIncludes)

SET(polycodeNetworking_SRCS
    Source/PolyClient.cpp
    Source/PolyPeer.cpp
    Source/PolyServer.cpp
    Source/PolySocket.cpp
)

SET(polycodeNetworking_HDRS
    Include/PolycodeNetworking.h
    Include/PolyClient.h
    Include/PolyPeer.h
    Include/PolyServer.h
    Include/PolyServerWorld.h
    Include/PolySocket.h
)

INCLUDE_DIRECTORIES(
    Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

ADD_LIBRARY(PolycodeNetworking ${polycodeNetworking_SRCS} ${polycodeNetworking_HDRS})

TARGET_LINK_LIBRARIES(PolycodeNetworking 
    Polycore 
    ${BOX2D_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${VORBISFILE_LIBRARY})
IF(APPLE)
    TARGET_LINK_LIBRARIES(PolycodeNetworking "-framework Cocoa")
ENDIF(APPLE)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeNetworking_HDRS} DESTINATION Modules/include)
    # install libraries
    INSTALL(TARGETS PolycodeNetworking DESTINATION Modules/lib)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)

