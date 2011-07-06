INCLUDE_DIRECTORIES(${PolyCode_SOURCE_DIR}/Tools/Dependencies/unzip11 Include)

SET(minizip_SRCS 
    ../../Dependencies/unzip11/ioapi.c
    ../../Dependencies/unzip11/ioapi.h
    ../../Dependencies/unzip11/zip.c
    ../../Dependencies/unzip11/zip.h
)

IF(POLYCODE_BUILD_SHARED)
    LINK_LIBRARIES(PolyCore)
    ADD_EXECUTABLE(polybuild ${minizip_SRCS} Source/polybuild.cpp Include/polybuild.h)
ENDIF(POLYCODE_BUILD_SHARED)

IF(POLYCODE_BUILD_STATIC)
    LINK_LIBRARIES(PolyCore_static)
    ADD_EXECUTABLE(polybuild_static ${minizip_SRCS} Source/polybuild.cpp Include/polybuild.h)
ENDIF(POLYCODE_BUILD_STATIC)
