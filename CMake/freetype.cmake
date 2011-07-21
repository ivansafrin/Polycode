CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(freetype C)

IF(NOT CMAKE_BUILD_TYPE)
    #SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_BUILD_TYPE "Release")
    MESSAGE("No CMAKE_BUILD_TYPE specified, defaulting to ${CMAKE_BUILD_TYPE}") 
ENDIF(NOT CMAKE_BUILD_TYPE)

# to distinguish between debug and release lib
SET(CMAKE_DEBUG_POSTFIX "_d")

SET(freetype_SRCS
    src/autofit/autofit.c
    src/bdf/bdf.c
    src/cff/cff.c
    src/base/ftbase.c
    src/base/ftbitmap.c
    src/cache/ftcache.c
    src/base/ftfstype.c
    src/base/ftgasp.c
    src/base/ftglyph.c
    src/gzip/ftgzip.c
    src/base/ftinit.c
    src/lzw/ftlzw.c
    src/base/ftstroke.c
    src/base/ftsystem.c
    src/smooth/smooth.c
    src/base/ftbbox.c
    src/base/ftmm.c
    src/base/ftpfr.c
    src/base/ftsynth.c
    src/base/fttype1.c
    src/base/ftwinfnt.c
    src/base/ftxf86.c
    src/base/ftlcdfil.c
    src/base/ftgxval.c
    src/base/ftotval.c
    src/base/ftpatent.c
    src/pcf/pcf.c
    src/pfr/pfr.c
    src/psaux/psaux.c
    src/pshinter/pshinter.c
    src/psnames/psmodule.c
    src/raster/raster.c
    src/sfnt/sfnt.c
    src/truetype/truetype.c
    src/type1/type1.c
    src/cid/type1cid.c
    src/type42/type42.c
    src/winfonts/winfnt.c
)

SET(freetype_HDRS
    include/ft2build.h
    include/freetype/config/ftconfig.h
    include/freetype/config/ftheader.h
    include/freetype/config/ftmodule.h
    include/freetype/config/ftoption.h
    include/freetype/config/ftstdlib.h
)

INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DFT2_BUILD_LIBRARY)
SET(COMPILE_DEFINITIONS_DEBUG FT_DEBUG_LEVEL_ERROR FT_DEBUG_LEVEL_TRACE)

IF(WIN32)
    LIST(APPEND freetype_SRCS builds/win32/ftdebug.c)
ENDIF(WIN32)

ADD_LIBRARY(freetype ${freetype_SRCS} ${freetype_HDRS})

INSTALL(TARGETS freetype
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)

INSTALL(DIRECTORY include/ DESTINATION include)

