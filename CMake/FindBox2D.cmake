# Locate Box2D library 
# This module defines 
# BOX2D_LIBRARY, the name of the library to link against 
# BOX2D_FOUND, if false, do not try to link to Box2D
# BOX2D_INCLUDE_DIR, where to find Box2D headers 
# 
# Created by Sven-Hendrik Haase. Based on the FindZLIB.cmake module.

IF(BOX2D_INCLUDE_DIR)
  # Already in cache, be silent
  SET(BOX2D_FIND_QUIETLY TRUE)
ENDIF(BOX2D_INCLUDE_DIR)

FIND_PATH(BOX2D_INCLUDE_DIR Box2D/Box2D.h
  PATH_SUFFIXES include
)

FIND_LIBRARY(BOX2D_RELEASE_LIBRARY NAMES box2d Box2d BOX2D Box2D)
FIND_LIBRARY(BOX2D_DEBUG_LIBRARY NAMES box2d_d Box2d_d BOX2D_d Box2D_d)

IF(BOX2D_RELEASE_LIBRARY)
    IF(BOX2D_DEBUG_LIBRARY)
        SET(BOX2D_LIBRARY optimized "${BOX2D_RELEASE_LIBRARY}" debug "${BOX2D_DEBUG_LIBRARY}")
    ELSE()
        SET(BOX2D_LIBRARY "${BOX2D_RELEASE_LIBRARY}")        # Could add "general" keyword, but it is optional
    ENDIF()
ENDIF()

MARK_AS_ADVANCED(BOX2D_LIBRARY BOX2D_RELEASE_LIBRARY BOX2D_DEBUG_LIBRARY BOX2D_INCLUDE_DIR)

# Per-recommendation
SET(BOX2D_INCLUDE_DIRS "${BOX2D_INCLUDE_DIR}")
SET(BOX2D_LIBRARIES    "${BOX2D_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set BOX2D_FOUND to TRUE if 
# all listed variables are TRUE

INCLUDE(FindPackageHandleStandardArgs) 
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Box2D DEFAULT_MSG BOX2D_LIBRARY BOX2D_INCLUDE_DIR) 
