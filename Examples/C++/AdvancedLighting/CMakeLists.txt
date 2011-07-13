INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
	ADD_EXECUTABLE(AdvancedLighting ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(AdvancedLighting Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_EXECUTABLE(AdvancedLighting_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(AdvancedLighting_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)

