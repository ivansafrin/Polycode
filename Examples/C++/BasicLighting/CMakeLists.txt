INCLUDE_DIRECTORIES(.)

#IF(POLYCODE_BUILD_SHARED)
#	ADD_EXECUTABLE(BasicLighting_dynamic ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
#	TARGET_LINK_LIBRARIES(BasicLighting_dynamic Polycore_dynamic)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_EXECUTABLE(BasicLighting ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
TARGET_LINK_LIBRARIES(BasicLighting Polycore)
#ENDIF(POLYCODE_BUILD_STATIC)
