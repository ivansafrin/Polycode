
set(PNG_FIND_DEBUG TRUE CACHE BOOL "Also search for the debug version of the PNG library")

SET(LUA_SEARCH_PATHS
	${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/lib
	${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/include
	${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/include/libpng15
	${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies/lib
	${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies/lib
)

if(PNG_FIND_DEBUG)
	if(PNG_INCLUDE_DIR AND PNG_LIBRARY AND PNG_LIBRARY_DEBUG)
		set(PNG_FIND_QUIETLY TRUE)
	endif(PNG_INCLUDE_DIR AND PNG_LIBRARY AND PNG_LIBRARY_DEBUG)
else(PNG_FIND_DEBUG)
	if(PNG_INCLUDE_DIR AND PNG_LIBRARY)
		set(PNG_FIND_QUIETLY TRUE)
	endif(PNG_INCLUDE_DIR AND PNG_LIBRARY)
endif(PNG_FIND_DEBUG)

find_path(PNG_INCLUDE_DIR png.h DOC "Directory containing png.h")

find_library(PNG_LIBRARY NAMES png libpng png15 libpng15 libpng15_static DOC "Path to PNG library")
if(PNG_FIND_DEBUG)
	find_library(PNG_LIBRARY_DEBUG NAMES pngd libpngd png15d libpng15d libpng15_staticd DOC "Path to PNG debug library")
endif(PNG_FIND_DEBUG)

# handle the QUIETLY and REQUIRED arguments and set PNG_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PNG DEFAULT_MSG PNG_LIBRARY PNG_INCLUDE_DIR)

if(PNG_FOUND)
	if(PNG_FIND_DEBUG)
		if(NOT PNG_LIBRARY_DEBUG)
			set(PNG_LIBRARY_DEBUG ${PNG_LIBRARY})
		endif(NOT PNG_LIBRARY_DEBUG)
		set(PNG_LIBRARIES debug ${PNG_LIBRARY_DEBUG} optimized ${PNG_LIBRARY})
	else(PNG_FIND_DEBUG)
		set(PNG_LIBRARIES ${PNG_LIBRARY})
	endif(PNG_FIND_DEBUG)
else(PNG_FOUND)
   SET(PNG_LIBRARIES )
endif(PNG_FOUND)
