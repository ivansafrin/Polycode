# Install script for directory: /Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/kristian/Dropbox/github/Polycode/Release/Darwin/Framework/")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/include" TYPE FILE FILES
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolycodeUI.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIElement.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIHSizer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIVSizer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIBox.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIMenu.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIButton.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUICheckBox.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIComboBox.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIColorBox.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIEvent.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIHScrollBar.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIHSlider.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIImageButton.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIScrollContainer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUITextInput.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUITree.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUITreeContainer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUITreeEvent.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIVScrollBar.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIWindow.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIFileDialog.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/UI/Include/PolyUIMenuBar.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/lib" TYPE STATIC_LIBRARY FILES "/Users/kristian/Dropbox/github/Polycode/Standalone/Modules/Contents/UI/libPolycodeUI.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeUI.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeUI.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeUI.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

