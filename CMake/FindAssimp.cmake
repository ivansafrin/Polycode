# Based on http://freya3d.org/browser/CMakeFind/FindAssimp.cmake
# Based on http://www.daimi.au.dk/~cgd/code/extensions/Assimp/FindAssimp.cmake
# - Try to find Assimp
# Once done this will define
#
#  ASSIMP_FOUND - system has Assimp
#  ASSIMP_INCLUDE_DIR - the Assimp include directory
#  ASSIMP_LIBRARY - Link these to use Assimp
#  ASSIMP_LIBRARIES


find_path (ASSIMP_INCLUDE_DIR NAMES assimp.h
  PATH_SUFFIXES include/assimp include
  PATHS ENV{CPATH} $ENV{ASSIMP_DIR} $ENV{ASSIMP_DIR}/include $ENV{INCLUDE} $ENV{INCLUDE}
  /usr/include /usr/local/include /opt/local/include ENV INCLUDE/assimp
  ${ASSIMP_ROOT}/include 
)
 
set (LIB_PATHS $ENV{LD_LIBRARY_PATH} $ENV{LIBRARY_PATH} $ENV{LIB}
  /usr/lib /usr/local/lib /opt/local/lib
  ${ASSIMP_INCLUDE_DIR}/../lib)

find_library (ASSIMP_LIBRARY_DEBUG NAMES assimpd PATHS ${LIB_PATHS})
find_library (ASSIMP_LIBRARY_RELEASE NAMES assimp PATHS ${LIB_PATHS})

if (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
  set(ASSIMP_FOUND TRUE)
endif()

if (ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
  if (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
    set (ASSIMP_LIBRARY debug ${ASSIMP_LIBRARY_DEBUG} optimized ${ASSIMP_LIBRARY_RELEASE} )
  else()
    set (ASSIMP_LIBRARY ${ASSIMP_LIBRARY_RELEASE})
  endif()
    # FIXME: This probably should be set for both cases
    set (ASSIMP_LIBRARIES debug ${ASSIMP_LIBRARY_DEBUG} optimized ${ASSIMP_LIBRARY_RELEASE})
endif()

if (ASSIMP_FOUND)
  mark_as_advanced (ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY ASSIMP_LIBRARIES)
endif()


