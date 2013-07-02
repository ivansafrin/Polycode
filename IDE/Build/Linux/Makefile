CC=g++
CFLAGS=-I../../Contents/Include -I../../../Release/Linux/Framework/Core/Dependencies/include -I../../../Release/Linux/Framework/Core/Dependencies/include/AL -I../../../Release/Linux/Framework/Core/include -I../../../Release/Linux/Framework/Modules/include -I../../../Release/Linux/Framework/Modules/Dependencies/include -I../../../Release/Linux/Framework/Modules/Dependencies/include/bullet -DUSE_POLYCODEUI_FILE_DIALOGS -DUSE_POLYCODEUI_MENUBAR
LDFLAGS=-lrt -ldl -lpthread ../../../Release/Linux/Framework/Core/lib/libPolycore.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libfreetype.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbisfile.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbis.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibogg.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libopenal.so ../../../Release/Linux/Framework/Core/Dependencies/lib/libphysfs.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libpng15.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../../Release/Linux/Framework/Modules/lib/libPolycode2DPhysics.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBox2D.a ../../../Release/Linux/Framework/Modules/lib/libPolycode3DPhysics.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBulletDynamics.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBulletCollision.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libLinearMath.a ../../../Release/Linux/Framework/Modules/lib/libPolycodeUI.a -lX11
LDFLAGS_DEBUG=-lrt -ldl -lpthread ../../../Release/Linux/Framework/Core/lib/libPolycore_d.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libfreetype_d.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbisfiled.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbisd.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libliboggd.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libopenal.so ../../../Release/Linux/Framework/Core/Dependencies/lib/libphysfsd.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libpng15d.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../../Release/Linux/Framework/Modules/lib/libPolycode2DPhysics_d.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBox2D_d.a ../../../Release/Linux/Framework/Modules/lib/libPolycode3DPhysics_d.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBulletDynamics_d.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libBulletCollision_d.a ../../../Release/Linux/Framework/Modules/Dependencies/lib/libLinearMath_d.a ../../../Release/Linux/Framework/Modules/lib/libPolycodeUI_d.a -lX11
SRCS=../../Contents/Source/ExampleBrowserWindow.cpp ../../Contents/Source/PolycodeEditorManager.cpp  ../../Contents/Source/PolycodeProject.cpp        ../../Contents/Source/PolycodeScreenEditor.cpp ../../Contents/Source/ExportProjectWindow.cpp  ../../Contents/Source/PolycodeFontEditor.cpp     ../../Contents/Source/PolycodeProjectBrowser.cpp ../../Contents/Source/PolycodeSpriteEditor.cpp ../../Contents/Source/NewFileWindow.cpp        ../../Contents/Source/PolycodeFrame.cpp          ../../Contents/Source/PolycodeProjectEditor.cpp  ../../Contents/Source/PolycodeTextEditor.cpp ../../Contents/Source/NewProjectWindow.cpp     ../../Contents/Source/PolycodeIDEApp.cpp         ../../Contents/Source/PolycodeProjectManager.cpp ../../Contents/Source/PolycodeToolLauncher.cpp ../../Contents/Source/PolycodeConsole.cpp      ../../Contents/Source/PolycodeImageEditor.cpp    ../../Contents/Source/PolycodeProps.cpp          ../../Contents/Source/TextureBrowser.cpp ../../Contents/Source/PolycodeEditor.cpp       ../../Contents/Source/PolycodeMaterialEditor.cpp ../../Contents/Source/PolycodeRemoteDebugger.cpp ../../Contents/Source/ToolWindows.cpp ../../Contents/Source/PolycodeClipboard.cpp ../../Contents/Source/SettingsWindow.cpp

default:
	mkdir -p ./Build
	$(CC) $(CFLAGS) -O2 main.cpp $(SRCS) -o ./Build/Polycode $(LDFLAGS)
	cp -R ../../Contents/Resources/* Build/
	cp ../../../Release/Linux/Framework/Core/Assets/default.pak Build/
	cp ../../../Release/Linux/Framework/Core/Assets/hdr.pak Build/
	cp -R ../../../Release/Linux/Standalone Build
debug:
	mkdir -p ./Build
	$(CC) $(CFLAGS) -g main.cpp $(SRCS) -o ./Build/Polycode $(LDFLAGS_DEBUG)
	cp -R ../../Contents/Resources/* Build/
	cp ../../../Release/Linux/Framework/Core/Assets/default.pak Build/
	cp ../../../Release/Linux/Framework/Core/Assets/hdr.pak Build/
	cp -R ../../../Release/Linux/Standalone Build

clean:
	rm -rf ./Build
	
