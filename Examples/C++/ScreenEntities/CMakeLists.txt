INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
	ADD_EXECUTABLE(ScreenEntities ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(ScreenEntities Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_EXECUTABLE(ScreenEntities_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(ScreenEntities_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)
