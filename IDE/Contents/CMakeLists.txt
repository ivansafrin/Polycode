# This CMakeLists.txt is a cross-platform alternative to the $Polycode/IDE/Build/$OS
# build systems. 
#
# It also demonstrates how Polycode projects other than the IDE can be built.
# First a few variables need to be set:
# * POLYCODE_ROOT_DIR
# * POLYCODE_RELEASE_DIR
# * POLYCODE_CMAKE_DIR
# * CMAKE_INSTALL_PREFIX
# Then we can simply include ${POLYCODE_CMAKE_DIR}/PolycodeDependencies.cmake
# After that, ${POLYCODE_DEPENDENCY_LIBS} will be set to the paths of our required
# link libraries, which we can simply add to our IDE project with TARGET_LINK_LIBRARIES

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(PolycodeIDE)

SET(POLYCODE_ROOT_DIR ${PolycodeIDE_SOURCE_DIR}/../../)
SET(POLYCODE_RELEASE_DIR ${POLYCODE_ROOT_DIR}/Release/${CMAKE_SYSTEM_NAME})
SET(POLYCODE_CMAKE_DIR ${POLYCODE_ROOT_DIR}/CMake)
SET(CMAKE_INSTALL_PREFIX ${POLYCODE_RELEASE_DIR}/Standalone/)

SET(CMAKE_PREFIX_PATH
    ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies
    ${POLYCODE_RELEASE_DIR}/Framework/Modules/Dependencies
    ${POLYCODE_RELEASE_DIR}/Framework/Tools/Dependencies)

SET(CMAKE_DEBUG_POSTFIX "_d")
SET(CMAKE_MODULE_PATH ${POLYCODE_ROOT_DIR}/CMake)
INCLUDE(${POLYCODE_CMAKE_DIR}/PolycodeDependencies.cmake)

IF(MSVC OR MINGW)
	SET(MAIN_CPP ../Build/Windows/main.cpp)
ELSEIF(APPLE)
		MESSAGE("Target system not currently supported.")
ELSE(MSVC OR MINGW)
	SET(MAIN_CPP ../Build/Linux/main.cpp)
ENDIF(MSVC OR MINGW)


SET(PolycodeIDE_SRCS
		${MAIN_CPP}
		Source/ExampleBrowserWindow.cpp
		Source/PolycodeProject.cpp
		Source/ExportProjectWindow.cpp
		Source/PolycodeProjectBrowser.cpp
		Source/NewFileWindow.cpp
		Source/PolycodeProjectEditor.cpp
		Source/NewProjectWindow.cpp
		Source/PolycodeProjectManager.cpp
		Source/PolycodeClipboard.cpp
		Source/PolycodeProps.cpp
		Source/PolycodeConsole.cpp
		Source/PolycodeRemoteDebugger.cpp
		Source/PolycodeEditor.cpp
		Source/PolycodeScreenEditor.cpp
		Source/PolycodeEditorManager.cpp
		Source/PolycodeSpriteEditor.cpp
		Source/PolycodeFontEditor.cpp
		Source/PolycodeTextEditor.cpp
		Source/PolycodeFrame.cpp
		Source/PolycodeToolLauncher.cpp
		Source/PolycodeIDEApp.cpp
		Source/SettingsWindow.cpp
		Source/PolycodeImageEditor.cpp
		Source/TextureBrowser.cpp
		Source/PolycodeMaterialEditor.cpp
		Source/ToolWindows.cpp
)

SET(PolycodeIDE_HDRS
		Include/ExampleBrowserWindow.h
		Include/PolycodeFrame.h
		Include/PolycodeProps.h
		Include/ExportProjectWindow.h
		Include/PolycodeGlobals.h
		Include/PolycodeRemoteDebugger.h
		Include/NewFileWindow.h
		Include/PolycodeIDEApp.h
		Include/PolycodeScreenEditor.h
		Include/NewProjectWindow.h
		Include/PolycodeImageEditor.h
		Include/PolycodeSpriteEditor.h
		Include/PolycodeClipboard.h
		Include/PolycodeMaterialEditor.h
		Include/PolycodeTextEditor.h
		Include/PolycodeConsole.h
		Include/PolycodeProject.h
		Include/PolycodeToolLauncher.h
		Include/PolycodeEditor.h
		Include/PolycodeProjectBrowser.h
		Include/SettingsWindow.h
		Include/PolycodeEditorManager.h
		Include/PolycodeProjectEditor.h
		Include/TextureBrowser.h
		Include/PolycodeFontEditor.h
		Include/PolycodeProjectManager.h
		Include/ToolWindows.h

)

INSTALL(FILES ${POLYCODE_ROOT_DIR}/LICENSE.txt
		DESTINATION ./)

# WIN32 makes it build a GUI application on windows(no effect on other platforms)
ADD_EXECUTABLE(PolycodeIDE WIN32 ${PolycodeIDE_SRCS} ${PolycodeIDE_HDRS})

IF(MSVC OR MINGW)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/bin/OpenAL32.dll DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/default.pak DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/hdr.pak DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/api.pak DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/UI.pak DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/Physics2D.pak DESTINATION bin)
	INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Player/Physics3D.pak DESTINATION bin)

	TARGET_LINK_LIBRARIES(PolycodeIDE
		${POLYCODE_DEPENDENCY_LIBS}
     )

ELSEIF(APPLE)
		MESSAGE("Target system not currently supported.")
ELSE(MSVC OR MINGW)
	TARGET_LINK_LIBRARIES(PolycodeIDE
		${POLYCODE_DEPENDENCY_LIBS}
	)
	
	# Install resources etc. after the build is finished
	ADD_CUSTOM_COMMAND(TARGET PolycodeIDE POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/ ${CMAKE_BINARY_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../../Release/Linux/Framework/Core/Assets/default.pak ${CMAKE_BINARY_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/../../Release/Linux/Standalone ${CMAKE_BINARY_DIR}/Standalone
	)

ENDIF(MSVC OR MINGW)
