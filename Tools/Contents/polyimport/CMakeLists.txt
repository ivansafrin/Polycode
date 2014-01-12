INCLUDE(PolycodeIncludes)

FIND_PACKAGE(Assimp REQUIRED)
INCLUDE_DIRECTORIES(
    ${ASSIMP_INCLUDE_DIR} 
    Include)

IF(WIN32)
	INCLUDE_DIRECTORIES(
	${Polycode_SOURCE_DIR}/Tools/Dependencies/getopt)
ENDIF(WIN32)

SET(CMAKE_DEBUG_POSTFIX "_d")

SET(getopt_SRCS 
    ../../Dependencies/getopt/getopt.c
    ../../Dependencies/getopt/getopt.h
)

#IF(POLYCODE_BUILD_SHARED)
#    ADD_EXECUTABLE(polyimport_dynamic Source/polyimport.cpp Include/polyimport.h)
#    TARGET_LINK_LIBRARIES(polyimport_dynamic Polycore_dynamic ${ASSIMP_LIBRARIES})
#ENDIF(POLYCODE_BUILD_SHARED)



#IF(POLYCODE_BUILD_STATIC)
IF(WIN32)
	ADD_EXECUTABLE(polyimport ${getopt_SRCS} Source/polyimport.cpp Include/polyimport.h)
ELSE()
	ADD_EXECUTABLE(polyimport Source/polyimport.cpp Include/polyimport.h)
ENDIF(WIN32)

IF(APPLE)
	TARGET_LINK_LIBRARIES(polyimport Polycore ${PHYSFS_LIBRARY}  ${ZLIB_LIBRARIES} ${ASSIMP_LIBRARY} "-framework IOKit" "-framework Cocoa")
ELSEIF(WIN32)
	TARGET_LINK_LIBRARIES(polyimport Polycore ${PHYSFS_LIBRARY}  ${ASSIMP_LIBRARY})
ELSE()
	TARGET_LINK_LIBRARIES(polyimport Polycore ${PHYSFS_LIBRARY}  ${ZLIB_LIBRARIES} ${ASSIMP_LIBRARY})
ENDIF(APPLE)
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)

    # install exes
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS polyimport DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Tools)
#    ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
    INSTALL(TARGETS polyimport DESTINATION Tools)
#    ENDIF(POLYCODE_BUILD_STATIC)

ENDIF(POLYCODE_INSTALL_FRAMEWORK)
