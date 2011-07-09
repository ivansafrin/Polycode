# Build a local version
INCLUDE(ExternalProject)

SET(openal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/OpenAL)

ExternalProject_Add(openal
	PREFIX ${openal_PREFIX}
	#URL http://connect.creativelabs.com/openal/Downloads/oalinst.zip
	URL http://kcat.strangesoft.net/openal-releases/openal-soft-1.13.tar.bz2
	URL_MD5 58b7d2809790c70681b825644c5f3614
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

# tell CMake to use this version
SET(OPENAL_INCLUDE_DIR ${openal_PREFIX}/include)
SET(OPENAL_LIBRARY ${openal_PREFIX}/lib/OpenAL32${CMAKE_LINK_LIBRARY_SUFFIX})

