# platform specific defines and include directories for win and sdl
IF(MSVC)
    ADD_DEFINITIONS(/D_UNICODE /DUNICODE)
    INCLUDE_DIRECTORIES(${PolyCode_SOURCE_DIR}/Core/Build/MSVC/Polycore)
ELSEIF(APPLE)
    ADD_DEFINITIONS(-DGL_GLEXT_PROTOTYPES)
ELSE(MSVC)
    ADD_DEFINITIONS(-DGL_GLEXT_PROTOTYPES)
    INCLUDE_DIRECTORIES(${PolyCode_SOURCE_DIR}/Core/Build/Linux)
ENDIF(MSVC)

# Set up common include directories
INCLUDE_DIRECTORIES(
    ${PolyCode_SOURCE_DIR}/Core/Contents/Include
    ${OPENGL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIR}
    ${PHYSFS_INCLUDE_DIR}
    ${OGG_INCLUDE_DIR}
    ${VORBISFILE_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
    ${OPENGLEXT_INCLUDE_DIR}
)