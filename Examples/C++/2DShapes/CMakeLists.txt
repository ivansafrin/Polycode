INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
    ADD_EXECUTABLE(2DShapes ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
    TARGET_LINK_LIBRARIES(2DShapes Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    ADD_EXECUTABLE(2DShapes_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(2DShapes_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)
