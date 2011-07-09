# Build a local version
INCLUDE(ExternalProject)

SET(freetype_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/freetype)

# Set the build target for the appropriate build
# TODO add other platforms
IF(MSVC10)
	# BUILD_COMMAND would be better but it returns a single string which is escaped when it shouldn't be
	SET(freetype_BUILD msbuild.exe builds/win32/vc2010/freetype.sln /p:Configuration=Release)
    SET(freetype_LIB ${freetype_PREFIX}/src/freetype/objs/win32/vc2010/freetype245.lib)
ENDIF(MSVC10)

ExternalProject_Add(freetype
	PREFIX ${freetype_PREFIX}
	URL http://download.savannah.gnu.org/releases/freetype/freetype-2.4.5.tar.gz
	URL_MD5 0e67460b312df905dc1cc1586690e7b2
	CONFIGURE_COMMAND cmake -E echo "Skipping configure step"
	BUILD_IN_SOURCE 1
	BUILD_COMMAND ${freetype_BUILD}
	INSTALL_COMMAND cmake -E echo "Skipping install step"
)

# tell CMake to use this version
SET(FREETYPE_INCLUDE_DIR ${freetype_PREFIX}/src/freetype/include)


