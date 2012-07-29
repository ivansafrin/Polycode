CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(lua51 C)

IF(NOT CMAKE_BUILD_TYPE)
    #SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_BUILD_TYPE "Release")
    MESSAGE("No CMAKE_BUILD_TYPE specified, defaulting to ${CMAKE_BUILD_TYPE}") 
ENDIF(NOT CMAKE_BUILD_TYPE)

# to distinguish between debug and release lib
SET(CMAKE_DEBUG_POSTFIX "d")

SET(lualib_SRCS 
    src/lapi.c src/lcode.c src/ldebug.c src/ldo.c src/ldump.c 
    src/lfunc.c src/lgc.c src/llex.c src/lmem.c src/lobject.c 
    src/lopcodes.c src/lparser.c src/lstate.c src/lstring.c
    src/ltable.c src/ltm.c src/lundump.c src/lvm.c src/lzio.c
    src/lauxlib.c src/lbaselib.c src/ldblib.c src/liolib.c 
    src/lmathlib.c src/loslib.c src/ltablib.c src/lstrlib.c 
    src/loadlib.c src/linit.c)

INCLUDE_DIRECTORIES(src)

IF(NOT MINGW AND NOT MSVC)
  ADD_DEFINITIONS(-DLUA_USE_POSIX -DLUA_USE_DLOPEN)
ENDIF(NOT MINGW AND NOT MSVC)

# We only want a static lib
ADD_LIBRARY(lualib ${lualib_SRCS})

SET_TARGET_PROPERTIES(lualib 
    PROPERTIES OUTPUT_NAME lua5.1)

INSTALL(TARGETS lualib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

INSTALL(FILES src/lua.h src/luaconf.h src/lualib.h src/lauxlib.h 
    DESTINATION include/lua5.1)

INSTALL(FILES etc/lua.hpp
    DESTINATION include/lua5.1)
