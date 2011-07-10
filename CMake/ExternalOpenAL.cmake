# Build a local version
INCLUDE(ExternalProject)

SET(openal_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/openal)

ExternalProject_Add(openal
    PREFIX ${openal_PREFIX}
    URL http://kcat.strangesoft.net/openal-releases/openal-soft-1.13.tar.bz2
    URL_MD5 58b7d2809790c70681b825644c5f3614
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(openal install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}
    FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY ${install_dir}/bin
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/bin)
INSTALL(DIRECTORY ${install_dir}/lib
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/lib)
