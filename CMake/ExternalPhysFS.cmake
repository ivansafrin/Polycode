# Build a local version
INCLUDE(ExternalProject)

SET(physfs_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/physfs)

ExternalProject_Add(physfs
    PREFIX ${physfs_PREFIX}
    URL http://offload1.icculus.org:9090/physfs/downloads/physfs-2.0.2.tar.gz
    URL_MD5 4e8927c3d30279b03e2592106eb9184a
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(physfs install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}
    FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY ${install_dir}/bin
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX})
INSTALL(DIRECTORY ${install_dir}/lib
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX})


