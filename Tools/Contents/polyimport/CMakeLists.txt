LINK_LIBRARIES(
    PolyCoreStatic
#    ${SDL_LIBRARY}
#    ${SDLMAIN_LIBRARY}
#    ${OPENGL_LIBRARIES}
#    ${OPENAL_LIBRARY}
#    ${PNG_LIBRARIES}
#    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
#    ${VORBISFILE_LIBRARY}
    assimp
)


INCLUDE_DIRECTORIES(${PolyCode_SOURCE_DIR}/Core/Contents/Include Include /usr/include/assimp)
ADD_EXECUTABLE(polyimport Source/polyimport.cpp Include/polyimport.h)
