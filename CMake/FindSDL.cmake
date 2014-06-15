# Copied from http://code.google.com/p/osgaudio/source/browse/trunk/CMakeModules/FindVorbis.cmake
# Locate Vorbis
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building Vorbis.

FIND_PATH(SDL_INCLUDE_DIR
	NAMES SDL.h
	PATHS $ENV{INCLUDE} $ENV{CPATH}
	PATH_SUFFIXES include SDL
)

SET(CMAKE_FIND_LIBRARY_SUFFIXES .so ${CMAKE_FIND_LIBRARY_SUFFIXES})
FIND_LIBRARY(SDL_LIBRARY 
	NAMES SDL libSDL
	PATHS $ENV{LD_LIBRARY_PATH} $ENV{LIBRARY_PATH} $ENV{LIB}
)

IF(SDL_LIBRARY)
	SET(SDL_LIBRARIES "${SDL_LIBRARY}")		# Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL DEFAULT_MSG SDL_LIBRARIES SDL_INCLUDE_DIR)
