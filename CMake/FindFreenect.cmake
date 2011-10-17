# Based on http://freya3d.org/browser/CMakeFind/FindFreenect.cmake
# Based on http://www.daimi.au.dk/~cgd/code/extensions/Freenect/FindFreenect.cmake
# - Try to find Freenect
# Once done this will define
#
#  FREENECT_FOUND - system has Freenect
#  FREENECT_INCLUDE_DIR - the Freenect include directory
#  FREENECT_LIBRARY - Link these to use Freenect
#  FREENECT_LIBRARIES

SET(FREENECT_SEARCH_PATHS
	${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies/lib
	${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies/include
)


find_path (FREENECT_INCLUDE_DIR NAMES libfreenect.h
	HINTS
	NO_DEFAULT_PATH
	NO_CMAKE_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
	NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_PATH
	CMAKE_FIND_FRAMEWORK NEVER
	PATH_SUFFIXES lib lib64 win32/Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
	PATHS ${FREENECT_SEARCH_PATHS}
)
 
find_library (FREENECT_LIBRARY_DEBUG NAMES freenectd libfreenect_d PATHS ${FREENECT_SEARCH_PATHS})
find_library (FREENECT_LIBRARY_RELEASE NAMES freenect PATHS ${FREENECT_SEARCH_PATHS})

if (FREENECT_INCLUDE_DIR AND FREENECT_LIBRARY_RELEASE)
  set(FREENECT_FOUND TRUE)
endif()

if (FREENECT_LIBRARY_RELEASE)
    set (FREENECT_LIBRARY ${FREENECT_LIBRARY_RELEASE})
endif()

if (FREENECT_LIBRARY_DEBUG AND FREENECT_LIBRARY_RELEASE)
    set (FREENECT_LIBRARY debug ${FREENECT_LIBRARY_DEBUG} optimized ${FREENECT_LIBRARY_RELEASE} )
endif()


if (FREENECT_FOUND)
  MESSAGE("-- Found Freenect ${FREENECT_LIBRARIES}")
  mark_as_advanced (FREENECT_INCLUDE_DIR FREENECT_LIBRARY FREENECT_LIBRARIES)
endif()


