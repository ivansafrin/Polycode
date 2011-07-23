INCLUDE_DIRECTORIES(.)

#IF(POLYCODE_BUILD_SHARED)
#	ADD_EXECUTABLE(BasicImage_dynamic ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
#	TARGET_LINK_LIBRARIES(BasicImage_dynamic Polycore_dynamic)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_EXECUTABLE(BasicImage ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
TARGET_LINK_LIBRARIES(BasicImage Polycore)
#ENDIF(POLYCODE_BUILD_STATIC)

