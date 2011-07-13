# Build a local version
INCLUDE(ExternalProject)

SET(openal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/openal)

ExternalProject_Add(openal
    PREFIX ${openal_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}

    URL http://kcat.strangesoft.net/openal-releases/openal-soft-1.13.tar.bz2
    URL_MD5 58b7d2809790c70681b825644c5f3614
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(openal install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")

# install debug lib
INSTALL(FILES ${install_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OpenAL32${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Debug
    RENAME OpenAL32d${CMAKE_STATIC_LIBRARY_SUFFIX})

# install release lib
INSTALL(FILES ${install_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OpenAL32${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Release)

# install debug shared library
INSTALL(FILES ${install_dir}/bin/${CMAKE_SHARED_LIBRARY_PREFIX}OpenAL32${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Debug
    RENAME OpenAL32d${CMAKE_SHARED_LIBRARY_SUFFIX})

# install release shared library
INSTALL(FILES ${install_dir}/bin/${CMAKE_SHARED_LIBRARY_PREFIX}OpenAL32${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Release)
