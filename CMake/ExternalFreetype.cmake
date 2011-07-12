# Build a local version of freetype
INCLUDE(ExternalProject)

SET(freetype_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freetype)

EXTERNALPROJECT_ADD(freetype
    PREFIX ${freetype_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://download.savannah.gnu.org/releases/freetype/freetype-2.4.5.tar.gz
    URL_MD5 0e67460b312df905dc1cc1586690e7b2

    PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PolycodeDependencies_SOURCE_DIR}/../CMake/freetype.cmake <SOURCE_DIR>/CMakeLists.txt

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(freetype install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")

# install debug libs
INSTALL(FILES ${install_dir}/lib/freetyped${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug)

# install release lib
INSTALL(FILES ${install_dir}/lib/freetype${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib/Release
    CONFIGURATIONS Release)
