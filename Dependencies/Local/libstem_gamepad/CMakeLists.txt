CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(stem_gamepad)

SET(POLYCODE_RELEASE_DIR ${stem_gamepad_SOURCE_DIR}/../../../Release/${CMAKE_SYSTEM_NAME})
SET(CMAKE_INSTALL_PREFIX ${POLYCODE_RELEASE_DIR}/Framework/)

SET(stem_gamepad_HDRS
	gamepad/Gamepad.h
	utilities/EventDispatcher.h
)

IF(APPLE)
SET(stem_gamepad_SRCS
	utilities/EventDispatcher.c
	gamepad/Gamepad_macosx.c
)
ENDIF(APPLE)

INCLUDE_DIRECTORIES(
    ${BOX2D_INCLUDE_DIRS}
	./
	utilities
	gamepad
)

SET(CMAKE_DEBUG_POSTFIX "_d")

ADD_LIBRARY(stem_gamepad ${stem_gamepad_SRCS} ${stem_gamepad_HDRS})

    # install headers
    INSTALL(FILES gamepad/Gamepad.h DESTINATION Core/Dependencies/Include/gamepad)
    INSTALL(FILES utilities/EventDispatcher.h DESTINATION Core/Dependencies/Include/utilities)

    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
    INSTALL(TARGETS stem_gamepad EXPORT stem_gamepad-targets DESTINATION Core/Dependencies/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
#    IF(POLYCODE_BUILD_STATIC)
#        INSTALL(TARGETS Polycode2DPhysics_static DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)

    INSTALL(EXPORT stem_gamepad-targets DESTINATION
        Core/Dependencies/lib/stem_gamepad)
