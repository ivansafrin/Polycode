INCLUDE_DIRECTORIES(.)

IF(POLYCODE_BUILD_SHARED)
	ADD_EXECUTABLE(2DTransforms ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(2DTransforms Polycore)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
	ADD_EXECUTABLE(2DTransforms_static ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
	TARGET_LINK_LIBRARIES(2DTransforms_static Polycore_static)
ENDIF(POLYCODE_BUILD_STATIC)

