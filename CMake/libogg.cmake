CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(libogg C)

IF(NOT CMAKE_BUILD_TYPE)
    #SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_BUILD_TYPE "Release")
    MESSAGE("No CMAKE_BUILD_TYPE specified, defaulting to ${CMAKE_BUILD_TYPE}") 
ENDIF(NOT CMAKE_BUILD_TYPE)

# to distinguish between debug and release lib
SET(CMAKE_DEBUG_POSTFIX "d")

SET(libogg_SRCS src/bitwise.c src/framing.c)
SET(libogg_HDRS include/ogg/ogg.h include/ogg/os_types.h)

INCLUDE_DIRECTORIES(include)

IF(MSVC)
    ADD_DEFINITIONS(/D_UNICODE /DUNICODE)
    LIST(APPEND libogg_SRCS win32/ogg.def)
ENDIF(MSVC)

ADD_LIBRARY(libogg_dynamic SHARED ${libogg_SRCS} ${libogg_HDRS})
ADD_LIBRARY(libogg_static ${libogg_SRCS} ${libogg_HDRS})

SET_TARGET_PROPERTIES(libogg_dynamic libogg_static 
    PROPERTIES OUTPUT_NAME libogg)

INSTALL(TARGETS libogg_dynamic libogg_static
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

INSTALL(FILES ${libogg_HDRS} DESTINATION include/ogg)

