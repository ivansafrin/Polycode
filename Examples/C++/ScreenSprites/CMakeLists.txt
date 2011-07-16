INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
	ADD_EXECUTABLE(ScreenSprites ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(ScreenSprites Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_EXECUTABLE(ScreenSprites_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(ScreenSprites_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)
