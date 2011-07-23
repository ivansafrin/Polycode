INCLUDE_DIRECTORIES(.)

#IF(POLYCODE_BUILD_SHARED)
#	ADD_EXECUTABLE(3DAudio_dynamic ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
#	TARGET_LINK_LIBRARIES(3DAudio_dynamic Polycore_dynamic)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_EXECUTABLE(3DAudio ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
TARGET_LINK_LIBRARIES(3DAudio Polycore)
#ENDIF(POLYCODE_BUILD_STATIC)

