# Build a local version of libogg, libvorbis and libvorbisfile
INCLUDE(ExternalProject)

SET(oggvorbis_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/oggvorbis)

IF(MSVC10)
    SET(target_dir "win32/VS2010")
    SET(ogg_TARGET_DIR ${target_dir})
    SET(vorbis_TARGET_DIR ${target_dir}/libvorbis)
    SET(vorbisfile_TARGET_DIR ${target_dir}/libvorbisfile)
    SET(vorbis_CONFIG "Release")
    SET(ogg_LIB_DIR ${target_dir}/Win32/Release)
    SET(vorbis_LIB_DIR ${vorbis_TARGET_DIR}/Win32/Release)
    SET(vorbisfile_LIB_DIR ${vorbisfile_TARGET_DIR}/Win32/Release)
    # copy libvorbis.lib where the libvorbisfile project will find it - only a problem because build_command won't build the solution
    SET(vorbis_INSTALL ${CMAKE_COMMAND} -E copy_if_different ${vorbis_LIB_DIR}/libvorbis.lib ${vorbis_TARGET_DIR}/../win32/release/libvorbis.lib)
ELSE()
    MESSAGE(ERROR "Generator support not implemented yet.")
ENDIF(MSVC10)

BUILD_COMMAND(ogg_TEMP TARGET ${ogg_TARGET_DIR}/libogg_dynamic CONFIGURATION ${vorbis_CONFIG})
BUILD_COMMAND(vorbis_TEMP TARGET ${vorbis_TARGET_DIR}/libvorbis_dynamic CONFIGURATION ${vorbis_CONFIG})
BUILD_COMMAND(vorbisfile_TEMP TARGET ${vorbisfile_TARGET_DIR}/libvorbisfile_dynamic CONFIGURATION ${vorbis_CONFIG})

# split build command string into list
STRING(REPLACE " " ";" ogg_BUILD ${ogg_TEMP})
STRING(REPLACE " " ";" vorbis_BUILD ${vorbis_TEMP})
STRING(REPLACE " " ";" vorbisfile_BUILD ${vorbisfile_TEMP})

ExternalProject_Add(ogg
    PREFIX ${oggvorbis_PREFIX}
    URL http://downloads.xiph.org/releases/ogg/libogg-1.2.2.tar.gz
    URL_MD5 5a9fcabc9a1b7c6f1cd75ddc78f36c56
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Skipping configure step"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${ogg_BUILD}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "Skipping install step"
)

ExternalProject_Add(vorbis
    DEPENDS ogg
    PREFIX ${oggvorbis_PREFIX}
    URL http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.2.tar.gz
    URL_MD5 c870b9bd5858a0ecb5275c14486d9554
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Skipping configure step"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${vorbis_BUILD}
    INSTALL_COMMAND ${vorbis_INSTALL}
)

ExternalProject_Get_Property(vorbis source_dir)

ExternalProject_Add(vorbisfile
    DEPENDS vorbis
    PREFIX ${oggvorbis_PREFIX}
    SOURCE_DIR ${source_dir}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Skipping configure step"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${vorbisfile_BUILD}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "Skipping install step"
)

# get the source dir for in source build
ExternalProject_Get_Property(ogg source_dir)

# install built files

# ogg headers and includes
INSTALL(DIRECTORY ${source_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}
    FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY ${source_dir}/${ogg_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/bin/
    FILES_MATCHING PATTERN "*${CMAKE_SHARED_LIBRARY_SUFFIX}")
INSTALL(DIRECTORY ${source_dir}/${ogg_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/lib/
    FILES_MATCHING PATTERN "*${CMAKE_LINK_LIBRARY_SUFFIX}")

ExternalProject_Get_Property(vorbis source_dir)

# vorbis headers
INSTALL(DIRECTORY ${source_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}
    FILES_MATCHING PATTERN "*.h")
    
# vorbis libraries
INSTALL(DIRECTORY ${source_dir}/${vorbis_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/bin/
    FILES_MATCHING PATTERN "*${CMAKE_SHARED_LIBRARY_SUFFIX}")
INSTALL(DIRECTORY ${source_dir}/${vorbis_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/lib/
    FILES_MATCHING PATTERN "*${CMAKE_LINK_LIBRARY_SUFFIX}")

# vorbisfile libraries
INSTALL(DIRECTORY ${source_dir}/${vorbisfile_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/bin/
    FILES_MATCHING PATTERN "*${CMAKE_SHARED_LIBRARY_SUFFIX}")
INSTALL(DIRECTORY ${source_dir}/${vorbisfile_LIB_DIR}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/lib/
    FILES_MATCHING PATTERN "*${CMAKE_LINK_LIBRARY_SUFFIX}")

