# Build a local version of zlib and libpng
INCLUDE(ExternalProject)

SET(zlib_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/zlib)

EXTERNALPROJECT_ADD(zlib
	PREFIX ${zlib_PREFIX}
	URL http://zlib.net/zlib-1.2.5.tar.gz
	URL_MD5 c735eab2d659a96e5a594c9e8541ad63
	PATCH_COMMAND ${CMAKE_COMMAND} -E remove <SOURCE_DIR>/zconf.h
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

SET(png_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/libpng)

EXTERNALPROJECT_ADD(libpng
	DEPENDS zlib
	PREFIX ${png_PREFIX}
	URL ftp://ftp.simplesystems.org/pub/libpng/png/src/libpng-1.5.4.tar.gz
	URL_MD5 dea4d1fd671160424923e92ff0cdda78
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_PREFIX_PATH=${zlib_PREFIX} # to find zlib
)

# tell CMake to use this version
#  PNG_INCLUDE_DIR, where to find png.h, etc.
#  PNG_LIBRARIES, the libraries to link against to use PNG.
#  PNG_DEFINITIONS - You should add_definitons(${PNG_DEFINITIONS}) before compiling code that includes png library files.
#  PNG_FOUND, If false, do not try to use PNG.

SET(PNG_INCLUDE_DIR ${png_PREFIX}/include)
SET(PNG_LIBRARIES ${png_PREFIX}/lib)

