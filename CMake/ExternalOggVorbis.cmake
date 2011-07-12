# Build a local version of libogg, libvorbis and libvorbisfile
INCLUDE(ExternalProject)

SET(oggvorbis_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/oggvorbis)

EXTERNALPROJECT_ADD(libogg
    PREFIX ${oggvorbis_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://downloads.xiph.org/releases/ogg/libogg-1.2.2.tar.gz
    URL_MD5 5a9fcabc9a1b7c6f1cd75ddc78f36c56

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/libogg.cmake <SOURCE_DIR>/CMakeLists.txt

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(libogg install_dir)

EXTERNALPROJECT_ADD(libvorbis
    DEPENDS libogg
    PREFIX ${oggvorbis_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.2.tar.gz
    URL_MD5 c870b9bd5858a0ecb5275c14486d9554

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/libvorbis.cmake <SOURCE_DIR>/CMakeLists.txt

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_PREFIX_PATH=${install_dir} # to find libogg
)

ExternalProject_Get_Property(libvorbis install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")

# install debug libs
INSTALL(FILES ${install_dir}/lib/liboggd${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/lib/libvorbisd${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/lib/libvorbisfiled${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug)

# install release lib
INSTALL(FILES ${install_dir}/lib/libogg${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Release
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/lib/libvorbis${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Release
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/lib/libvorbisfile${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Release
    CONFIGURATIONS Release)

# install debug shared library
INSTALL(FILES ${install_dir}/bin/liboggd${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Debug
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/bin/libvorbisd${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Debug
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/bin/libvorbisfiled${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Debug
    CONFIGURATIONS Debug)

# install release shared library
INSTALL(FILES ${install_dir}/bin/libogg${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Release
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/bin/libvorbis${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Release
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/bin/libvorbisfile${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin/Release
    CONFIGURATIONS Release)
