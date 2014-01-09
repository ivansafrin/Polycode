INCLUDE(PolycodeIncludes)

SET(polycodeUI_SRCS
    Source/PolyUIElement.cpp
    Source/PolyUIBox.cpp
    Source/PolyUIMenu.cpp
    Source/PolyUIHSizer.cpp
    Source/PolyUIVSizer.cpp
    Source/PolyUIButton.cpp
    Source/PolyUICheckBox.cpp
    Source/PolyUIComboBox.cpp
    Source/PolyUIColorBox.cpp
    Source/PolyUIEvent.cpp
    Source/PolyUIHScrollBar.cpp
    Source/PolyUIHSlider.cpp
    Source/PolyUIImageButton.cpp
    Source/PolyUIScrollContainer.cpp
    Source/PolyUITextInput.cpp
    Source/PolyUITree.cpp
    Source/PolyUITreeContainer.cpp
    Source/PolyUITreeEvent.cpp
    Source/PolyUIVScrollBar.cpp
    Source/PolyUIWindow.cpp
    Source/PolyUIFileDialog.cpp
    Source/PolyUIMenuBar.cpp
    Source/PolyUIIconSelector.cpp
)

SET(polycodeUI_HDRS
    Include/PolycodeUI.h
    Include/PolyUIElement.h
    Include/PolyUIHSizer.h
    Include/PolyUIVSizer.h
    Include/PolyUIBox.h
    Include/PolyUIMenu.h
    Include/PolyUIButton.h
    Include/PolyUICheckBox.h
    Include/PolyUIComboBox.h
    Include/PolyUIColorBox.h
    Include/PolyUIEvent.h
    Include/PolyUIHScrollBar.h
    Include/PolyUIHSlider.h
    Include/PolyUIImageButton.h
    Include/PolyUIScrollContainer.h
    Include/PolyUITextInput.h
    Include/PolyUITree.h
    Include/PolyUITreeContainer.h
    Include/PolyUITreeEvent.h
    Include/PolyUIVScrollBar.h
    Include/PolyUIWindow.h
    Include/PolyUIFileDialog.h
    Include/PolyUIMenuBar.h
    Include/PolyUIIconSelector.h
)

INCLUDE_DIRECTORIES(
    Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

ADD_LIBRARY(PolycodeUI ${polycodeUI_SRCS} ${polycodeUI_HDRS})

TARGET_LINK_LIBRARIES(PolycodeUI 
    Polycore 
    ${BOX2D_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${PNG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${PHYSFS_LIBRARY}
    ${VORBISFILE_LIBRARY})
IF(APPLE)
    TARGET_LINK_LIBRARIES(PolycodeUI "-framework Cocoa")
ENDIF(APPLE)

IF(POLYCODE_INSTALL_FRAMEWORK)
    
    # install headers
    INSTALL(FILES ${polycodeUI_HDRS} DESTINATION Modules/include)
    # install libraries
    INSTALL(TARGETS PolycodeUI DESTINATION Modules/lib)
    
ENDIF(POLYCODE_INSTALL_FRAMEWORK)

