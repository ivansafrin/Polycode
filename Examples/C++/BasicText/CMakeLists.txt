INCLUDE_DIRECTORIES(.)

#IF(POLYCODE_BUILD_SHARED)
#	ADD_EXECUTABLE(BasicText_dynamic ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
#	TARGET_LINK_LIBRARIES(BasicText_dynamic Polycore_dynamic)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_EXECUTABLE(BasicText ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
TARGET_LINK_LIBRARIES(BasicText Polycore)
#ENDIF(POLYCODE_BUILD_STATIC)
