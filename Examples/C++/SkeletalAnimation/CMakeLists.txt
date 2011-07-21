INCLUDE_DIRECTORIES(.)

#IF(POLYCODE_BUILD_SHARED)
#	ADD_EXECUTABLE(SkeletalAnimation_dynamic ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
#	TARGET_LINK_LIBRARIES(SkeletalAnimation_dynamic Polycore_dynamic)
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_EXECUTABLE(SkeletalAnimation ../main.cpp HelloPolycodeApp.cpp HelloPolycodeApp.h)
TARGET_LINK_LIBRARIES(SkeletalAnimation Polycore)
#ENDIF(POLYCODE_BUILD_STATIC)
