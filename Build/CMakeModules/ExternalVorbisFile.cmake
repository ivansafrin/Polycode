# Build a local version of libogg, libvorbis and libvorbisfile
INCLUDE(ExternalProject)

SET(ogg_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/vorbisfile)

SET(vorbis_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/vorbisfile)

# Set the build target for the appropriate build
# TODO add other platforms
IF(MSVC10)
	# BUILD_COMMAND would be better but it returns a single string which is escaped when it shouldn't be
	SET(ogg_BUILD msbuild.exe win32/VS2010/libogg_dynamic.sln /p:Configuration=Release)
ENDIF(MSVC10)

EXTERNALPROJECT_ADD(ogg
	PREFIX ${ogg_PREFIX}
	URL http://downloads.xiph.org/releases/ogg/libogg-1.2.2.tar.gz
	URL_MD5 5a9fcabc9a1b7c6f1cd75ddc78f36c56
	CONFIGURE_COMMAND cmake -E echo "Skipping configure step"
	BUILD_IN_SOURCE 1
	BUILD_COMMAND ${ogg_BUILD}
	INSTALL_COMMAND cmake -E echo "Skipping install step"
)


# Set the build target for the appropriate build
IF(MSVC10)
	SET(vorbis_BUILD msbuild.exe win32/VS2010/vorbis_dynamic.sln /p:Configuration=Release)
    SET(VORBISFILE_LIBRARY src/vorbis/win32/VS2010/Win32/Release/libvorbisfile.lib)
ENDIF(MSVC10)

EXTERNALPROJECT_ADD(vorbis
	DEPENDS ogg
	PREFIX ${vorbis_PREFIX}
	URL http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.2.tar.gz
	URL_MD5 c870b9bd5858a0ecb5275c14486d9554
	PATCH_COMMAND 
	CONFIGURE_COMMAND cmake -E echo "Skipping configure step"
	BUILD_IN_SOURCE 1
	BUILD_COMMAND ${vorbis_BUILD}
	INSTALL_COMMAND cmake -E echo "Skipping install step"
)

# tell CMake to use this version
SET(OGG_INCLUDE_DIR ${vorbis_PREFIX}/src/ogg/include)
SET(VORBISFILE_INCLUDE_DIR ${vorbis_PREFIX}/src/vorbis/include)


