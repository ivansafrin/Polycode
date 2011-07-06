INCLUDE_DIRECTORIES(${PolyCode_SOURCE_DIR}/Core/Contents/Include Include ${ASSIMP_INCLUDE_DIR})

IF(POLYCODE_BUILD_SHARED)
    ADD_EXECUTABLE(polyimport Source/polyimport.cpp Include/polyimport.h)
    TARGET_LINK_LIBRARIES(polyimport PolyCore ${ASSIMP_LIBRARY_RELEASE})
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    ADD_EXECUTABLE(polyimport_static Source/polyimport.cpp Include/polyimport.h)
    TARGET_LINK_LIBRARIES(polyimport_static PolyCore_static ${PHYSFS_LIBRARY} ${ASSIMP_LIBRARY_RELEASE})
ENDIF(POLYCODE_BUILD_STATIC)
