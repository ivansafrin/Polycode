INCLUDE(PolycodeIncludes)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/UI/Include
    Include
    ../../Contents/UI/Include
)

SET(polycodeUI_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/UILUA.cpp
    ../../Contents/UI/Source/PolyUIBox.cpp
    ../../Contents/UI/Source/PolyUIButton.cpp
    ../../Contents/UI/Source/PolyUICheckBox.cpp
    ../../Contents/UI/Source/PolyUIColorBox.cpp
    ../../Contents/UI/Source/PolyUIComboBox.cpp
    ../../Contents/UI/Source/PolyUIElement.cpp
    ../../Contents/UI/Source/PolyUIEvent.cpp
    ../../Contents/UI/Source/PolyUIHScrollBar.cpp
    ../../Contents/UI/Source/PolyUIHSizer.cpp
    ../../Contents/UI/Source/PolyUIHSlider.cpp
    ../../Contents/UI/Source/PolyUIImageButton.cpp
    ../../Contents/UI/Source/PolyUIScrollContainer.cpp
    ../../Contents/UI/Source/PolyUITextInput.cpp
    ../../Contents/UI/Source/PolyUITree.cpp
    ../../Contents/UI/Source/PolyUITreeContainer.cpp
    ../../Contents/UI/Source/PolyUITreeEvent.cpp
    ../../Contents/UI/Source/PolyUIVScrollBar.cpp
    ../../Contents/UI/Source/PolyUIVSizer.cpp
    ../../Contents/UI/Source/PolyUIWindow.cpp
)

SET(polycodeUI_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/UILUA.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/UILUAWrappers.h
    ../../Contents/UI/Include/PolyUIBox.h
    ../../Contents/UI/Include/PolyUIButton.h
    ../../Contents/UI/Include/PolyUICheckBox.h
    ../../Contents/UI/Include/PolyUIColorBox.h
    ../../Contents/UI/Include/PolyUIComboBox.h
    ../../Contents/UI/Include/PolyUIElement.h
    ../../Contents/UI/Include/PolyUIEvent.h
    ../../Contents/UI/Include/PolyUIHScrollBar.h
    ../../Contents/UI/Include/PolyUIHSizer.h
    ../../Contents/UI/Include/PolyUIHSlider.h
    ../../Contents/UI/Include/PolyUIImageButton.h
    ../../Contents/UI/Include/PolyUIScrollContainer.h
    ../../Contents/UI/Include/PolyUITextInput.h
    ../../Contents/UI/Include/PolyUITree.h
    ../../Contents/UI/Include/PolyUITreeContainer.h
    ../../Contents/UI/Include/PolyUITreeEvent.h
    ../../Contents/UI/Include/PolyUIVScrollBar.h
    ../../Contents/UI/Include/PolyUIVSizer.h
    ../../Contents/UI/Include/PolyUIWindow.h
    ../../Contents/UI/Include/PolycodeUI.h
)

ADD_LIBRARY(UI SHARED ${polycodeUI_SRCS} ${polycodeUI_HDRS})

SET_SOURCE_FILES_PROPERTIES(Source/UILUA.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/UILUAWrappers.h PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(Include/UILUA.h PROPERTIES GENERATED 1)
ADD_DEPENDENCIES(UI PolycodeLuaGenerate)

SET(CMAKE_DEBUG_POSTFIX "_d")

SET_TARGET_PROPERTIES(UI PROPERTIES PREFIX "")

IF(APPLE)
TARGET_LINK_LIBRARIES(UI
	Polycore
	${LUA_LIBRARY}
	"-framework Cocoa"
	"-framework IOKit"
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
		${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARIES}
        ${VORBIS_LIBRARIES}
        ${VORBISFILE_LIBRARIES}
        ${EXTRA_LIBS})
ELSEIF(MSVC OR MINGW)

	SET(WIN_EXTRA_LIBS ${ZLIB_LIBRARIES} opengl32 glu32 winmm ws2_32)

TARGET_LINK_LIBRARIES(UI
	Polycore
	${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARIES}
        ${VORBIS_LIBRARIES}
        ${VORBISFILE_LIBRARIES}
        ${EXTRA_LIBS}
        ${WIN_EXTRA_LIBS})

ELSE(APPLE)

TARGET_LINK_LIBRARIES(UI
	Polycore
	${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARIES}
        ${VORBIS_LIBRARIES}
        ${VORBISFILE_LIBRARIES}
        ${EXTRA_LIBS})
          
ENDIF(APPLE)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeUI_HDRS} 
        DESTINATION Bindings/Lua/Modules/UI/include)

    INSTALL(DIRECTORY API DESTINATION Bindings/Lua/Modules/UI)
	
    # install libraries
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS PolycodeLua_dynamic
#            DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib)
#    ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
     INSTALL(TARGETS UI
         DESTINATION Bindings/Lua/Modules/UI/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)