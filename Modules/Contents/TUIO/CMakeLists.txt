INCLUDE(PolycodeIncludes)

SET(polycodeTUIO_SRCS
    Source/IpEndpointName.cpp
    Source/OscOutboundPacketStream.cpp
    Source/OscPrintReceivedElements.cpp
    Source/OscReceivedElements.cpp
    Source/OscTypes.cpp
    Source/TuioClient.cpp
    Source/TUIOInputModule.cpp
    Source/TuioServer.cpp
    Source/TuioTime.cpp
)

SET(polycodeTUIO_HDRS
    Include/TuioClient.h
    Include/TuioContainer.h
    Include/TuioCursor.h
    Include/TUIOInputModule.h
    Include/TuioListener.h
    Include/TuioObject.h
    Include/TuioPoint.h
    Include/TuioServer.h
    Include/TuioTime.h
)

IF(MSVC)
    LIST(APPEND polycodeTUIO_SRCS Source/win32/NetworkingUtils.cpp)
    LIST(APPEND polycodeTUIO_SRCS Source/win32/UdpSocket.cpp) 
ELSE(MSVC)
    LIST(APPEND polycodeTUIO_SRCS Source/posix/NetworkingUtils.cpp)
    LIST(APPEND polycodeTUIO_SRCS Source/posix/UdpSocket.cpp) 
ENDIF(MSVC)


INCLUDE_DIRECTORIES(
    Include
    Include/osc
    Include/ip
)

SET(CMAKE_DEBUG_POSTFIX "_d")

ADD_LIBRARY(PolycodeTUIO ${polycodeTUIO_SRCS} ${polycodeTUIO_HDRS})

TARGET_LINK_LIBRARIES(PolycodeTUIO
    Polycore 
    ${BOX2D_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${VORBISFILE_LIBRARY})
IF(APPLE)
    TARGET_LINK_LIBRARIES(PolycodeTUIO "-framework Cocoa")
ENDIF(APPLE)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeTUIO_HDRS} DESTINATION Modules/include)
    INSTALL(DIRECTORY Include/ip DESTINATION Modules/include)
    INSTALL(DIRECTORY Include/osc DESTINATION Modules/include)    
    # install libraries
    INSTALL(TARGETS PolycodeTUIO DESTINATION Modules/lib)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)

