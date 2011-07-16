INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
	ADD_EXECUTABLE(BasicLighting ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(BasicLighting Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_EXECUTABLE(BasicLighting_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(BasicLighting_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)
