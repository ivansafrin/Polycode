# Based on http://freya3d.org/browser/CMakeFind/FindAssimp.cmake
# Based on http://www.daimi.au.dk/~cgd/code/extensions/Assimp/FindAssimp.cmake
# - Try to find Assimp
# Once done this will define
#
#  ASSIMP_FOUND - system has Assimp
#  ASSIMP_INCLUDE_DIR - the Assimp include directory
#  ASSIMP_LIBRARY - Link these to use Assimp
#  ASSIMP_LIBRARIES

SET(ASSIMP_SEARCH_PATHS
	${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies/lib
	${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies/include/assimp
	${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies/include/
)


find_path (ASSIMP_INCLUDE_DIR NAMES assimp.h
	HINTS
	NO_DEFAULT_PATH
	NO_CMAKE_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_PATH
	CMAKE_FIND_FRAMEWORK NEVER
	PATH_SUFFIXES lib lib64 win32/Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
	PATHS ${ASSIMP_SEARCH_PATHS}
)
 
find_library (ASSIMP_LIBRARY_DEBUG NAMES assimpd libassimpd libassimp_d PATHS ${ASSIMP_SEARCH_PATHS})
find_library (ASSIMP_LIBRARY_RELEASE NAMES assimp libassimp PATHS ${ASSIMP_SEARCH_PATHS})

if (ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY_RELEASE)
  set(ASSIMP_FOUND TRUE)
endif()

if (ASSIMP_LIBRARY_RELEASE)
    set (ASSIMP_LIBRARY ${ASSIMP_LIBRARY_RELEASE})
endif()

if (ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
    set (ASSIMP_LIBRARY debug ${ASSIMP_LIBRARY_DEBUG} optimized ${ASSIMP_LIBRARY_RELEASE} )
endif()


if (ASSIMP_FOUND)
  MESSAGE("-- Found Assimp ${ASSIMP_LIBRARIES}")
  mark_as_advanced (ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY ASSIMP_LIBRARIES)
endif()


