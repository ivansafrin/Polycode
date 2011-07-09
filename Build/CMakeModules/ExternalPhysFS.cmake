# Build a local version
INCLUDE(ExternalProject)

SET(physfs_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/physfs)

ExternalProject_Add(physfs
	PREFIX ${physfs_PREFIX}
	URL http://offload1.icculus.org:9090/physfs/downloads/physfs-2.0.2.tar.gz
	URL_MD5 4e8927c3d30279b03e2592106eb9184a
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

# tell CMake to use this version
SET(PHYSFS_INCLUDE_DIR)
SET(PHYSFS_LIBRARY)
SET(PHYSFS_FOUND)
