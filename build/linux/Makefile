CC=g++
SRCDIR=../../src
ASSETDIR=../../assets

.SUFFIXES: .io .do .dio

SRCCORE = $(SRCDIR)/core/lodepng.cpp $(SRCDIR)/core/PolyBasicFileProvider.cpp $(SRCDIR)/core/PolyBezierCurve.cpp $(SRCDIR)/core/PolyBone.cpp $(SRCDIR)/core/PolyCamera.cpp $(SRCDIR)/core/PolyClient.cpp $(SRCDIR)/core/PolyColor.cpp $(SRCDIR)/core/PolyConfig.cpp $(SRCDIR)/core/PolyCore.cpp $(SRCDIR)/core/PolyCoreFileProvider.cpp $(SRCDIR)/core/PolyCoreInput.cpp $(SRCDIR)/core/PolyCoreServices.cpp $(SRCDIR)/core/PolyCubemap.cpp $(SRCDIR)/core/PolyData.cpp $(SRCDIR)/core/PolyEntity.cpp $(SRCDIR)/core/PolyEvent.cpp $(SRCDIR)/core/PolyEventDispatcher.cpp $(SRCDIR)/core/PolyEventHandler.cpp $(SRCDIR)/core/PolyFont.cpp $(SRCDIR)/core/PolyFontGlyphSheet.cpp $(SRCDIR)/core/PolyFontManager.cpp $(SRCDIR)/core/PolyGPUDrawBuffer.cpp $(SRCDIR)/core/PolyImage.cpp $(SRCDIR)/core/PolyInputEvent.cpp $(SRCDIR)/core/PolyLabel.cpp $(SRCDIR)/core/PolyLogger.cpp $(SRCDIR)/core/PolyMaterial.cpp $(SRCDIR)/core/PolyMaterialManager.cpp $(SRCDIR)/core/PolyMatrix4.cpp $(SRCDIR)/core/PolyMesh.cpp $(SRCDIR)/core/PolyObject.cpp $(SRCDIR)/core/PolyOpenGLGraphicsInterface.cpp $(SRCDIR)/core/PolyPAAudioInterface.cpp $(SRCDIR)/core/PolyParticleEmitter.cpp $(SRCDIR)/core/PolyPeer.cpp $(SRCDIR)/core/PolyPerlin.cpp $(SRCDIR)/core/PolyPhysFSFileProvider.cpp $(SRCDIR)/core/PolyQuaternion.cpp $(SRCDIR)/core/PolyQuaternionCurve.cpp $(SRCDIR)/core/PolyRay.cpp $(SRCDIR)/core/PolyRectangle.cpp $(SRCDIR)/core/PolyRenderDataArray.cpp $(SRCDIR)/core/PolyRenderer.cpp $(SRCDIR)/core/PolyResource.cpp $(SRCDIR)/core/PolyResourceManager.cpp $(SRCDIR)/core/PolyScene.cpp $(SRCDIR)/core/PolySceneEntityInstance.cpp $(SRCDIR)/core/PolySceneImage.cpp $(SRCDIR)/core/PolySceneLabel.cpp $(SRCDIR)/core/PolySceneLight.cpp $(SRCDIR)/core/PolySceneLine.cpp $(SRCDIR)/core/PolySceneManager.cpp $(SRCDIR)/core/PolySceneMesh.cpp $(SRCDIR)/core/PolyScenePrimitive.cpp $(SRCDIR)/core/PolySceneRenderTexture.cpp $(SRCDIR)/core/PolySceneSound.cpp $(SRCDIR)/core/PolySceneSprite.cpp $(SRCDIR)/core/PolyServer.cpp $(SRCDIR)/core/PolyShader.cpp $(SRCDIR)/core/PolySkeleton.cpp $(SRCDIR)/core/PolySocket.cpp $(SRCDIR)/core/PolySound.cpp $(SRCDIR)/core/PolySoundManager.cpp $(SRCDIR)/core/PolyString.cpp $(SRCDIR)/core/PolyTexture.cpp $(SRCDIR)/core/PolyThreaded.cpp $(SRCDIR)/core/PolyTimer.cpp $(SRCDIR)/core/PolyTimerManager.cpp $(SRCDIR)/core/PolyTween.cpp $(SRCDIR)/core/PolyTweenManager.cpp $(SRCDIR)/core/PolyVector2.cpp $(SRCDIR)/core/PolyVector3.cpp $(SRCDIR)/core/PolyVector4.cpp $(SRCDIR)/core/rgbe.cpp $(SRCDIR)/core/tinystr.cpp $(SRCDIR)/core/tinyxml.cpp $(SRCDIR)/core/tinyxmlerror.cpp $(SRCDIR)/core/tinyxmlparser.cpp $(SRCDIR)/core/PolySDLCore.cpp $(SRCDIR)/view/linux/PolycodeView.cpp
OBJCORE=$(SRCCORE:.cpp=.o)
DOBJCORE=$(SRCCORE:.cpp=.do)

SRCUI=$(SRCDIR)/modules/ui/PolyUIBox.cpp $(SRCDIR)/modules/ui/PolyUIButton.cpp $(SRCDIR)/modules/ui/PolyUICheckBox.cpp $(SRCDIR)/modules/ui/PolyUIColorBox.cpp $(SRCDIR)/modules/ui/PolyUIComboBox.cpp $(SRCDIR)/modules/ui/PolyUIElement.cpp $(SRCDIR)/modules/ui/PolyUIEvent.cpp $(SRCDIR)/modules/ui/PolyUIFileDialog.cpp $(SRCDIR)/modules/ui/PolyUIHScrollBar.cpp $(SRCDIR)/modules/ui/PolyUIHSizer.cpp $(SRCDIR)/modules/ui/PolyUIHSlider.cpp $(SRCDIR)/modules/ui/PolyUIIconSelector.cpp $(SRCDIR)/modules/ui/PolyUIImageButton.cpp $(SRCDIR)/modules/ui/PolyUIMenu.cpp $(SRCDIR)/modules/ui/PolyUIMenuBar.cpp $(SRCDIR)/modules/ui/PolyUIScrollContainer.cpp $(SRCDIR)/modules/ui/PolyUITextInput.cpp $(SRCDIR)/modules/ui/PolyUITree.cpp $(SRCDIR)/modules/ui/PolyUITreeContainer.cpp $(SRCDIR)/modules/ui/PolyUITreeEvent.cpp $(SRCDIR)/modules/ui/PolyUIVScrollBar.cpp $(SRCDIR)/modules/ui/PolyUIVSizer.cpp $(SRCDIR)/modules/ui/PolyUIWindow.cpp
OBJUI=$(SRCUI:.cpp=.o)
DOBJUI=$(SRCUI:.cpp=.do)

SRCTEMPLATE=TemplateApp/PolycodeTemplateApp.cpp TemplateApp/PolycodeTemplate.cpp
OBJTEMPLATE=$(SRCTEMPLATE:.cpp=.o)
DOBJTEMPLATE=$(SRCTEMPLATE:.cpp=.do)

SRCSTUDIO=Studio/main.cpp $(SRCDIR)/ide/EditorGrid.cpp $(SRCDIR)/ide/EntityEditorPropertyView.cpp $(SRCDIR)/ide/EntityEditorSettingsView.cpp $(SRCDIR)/ide/EntityEditorTreeView.cpp $(SRCDIR)/ide/ExampleBrowserWindow.cpp $(SRCDIR)/ide/ExportProjectWindow.cpp $(SRCDIR)/ide/NewFileWindow.cpp $(SRCDIR)/ide/NewProjectWindow.cpp $(SRCDIR)/ide/PolycodeClipboard.cpp $(SRCDIR)/ide/PolycodeConsole.cpp $(SRCDIR)/ide/PolycodeEditor.cpp $(SRCDIR)/ide/PolycodeEditorManager.cpp $(SRCDIR)/ide/PolycodeEntityEditor.cpp $(SRCDIR)/ide/PolycodeFontEditor.cpp $(SRCDIR)/ide/PolycodeFrame.cpp $(SRCDIR)/ide/PolycodeIDEApp.cpp $(SRCDIR)/ide/PolycodeImageEditor.cpp $(SRCDIR)/ide/PolycodeMaterialEditor.cpp $(SRCDIR)/ide/PolycodeMeshEditor.cpp $(SRCDIR)/ide/PolycodeProject.cpp $(SRCDIR)/ide/PolycodeProjectBrowser.cpp $(SRCDIR)/ide/PolycodeProjectEditor.cpp $(SRCDIR)/ide/PolycodeProjectManager.cpp $(SRCDIR)/ide/PolycodeProps.cpp $(SRCDIR)/ide/PolycodeRemoteDebugger.cpp $(SRCDIR)/ide/PolycodeSoundEditor.cpp $(SRCDIR)/ide/PolycodeSpriteEditor.cpp $(SRCDIR)/ide/PolycodeTextEditor.cpp $(SRCDIR)/ide/PolycodeToolLauncher.cpp $(SRCDIR)/ide/SettingsWindow.cpp $(SRCDIR)/ide/TextureBrowser.cpp $(SRCDIR)/ide/ToolWindows.cpp $(SRCDIR)/ide/TrackballCamera.cpp $(SRCDIR)/ide/TransformGizmo.cpp
OBJSTUDIO=$(SRCSTUDIO:.cpp=.io)
DOBJSTUDIO=$(SRCSTUDIO:.cpp=.dio)

CFLAGS=-I../../include -DUSE_X11
CFLAGSSTUDIO=$(CFLAGS) -DUSE_POLYCODEUI_FILE_DIALOGS -DUSE_POLYCODEUI_MENUBAR

LIBDIR=../../lib/linux

OPTFLAGS=-O2
DEBUGFLAGS=-g -DDEBUG

LDFLAGSTEMPLATE=-L$(LIBDIR) $(OPTFLAGS) -pthread -lPolycore -lfreetype -lpng -lphysfs -lvorbisfile -lvorbis -logg -lportaudio -lasound -lz -lSDL -lGLEW -lGL -lX11 -lrt -llua -ldl
DLDFLAGSTEMPLATE=-L$(LIBDIR) -pthread -lPolycored -lfreetype -lpng -lphysfs -lvorbisfile -lvorbis -logg -lportaudio -lasound -lz -lSDL -lGLEW -lGL -lX11 -lrt -llua -ldl

LDFLAGSSTUDIO=-L$(LIBDIR) $(OPTFLAGS) -pthread -lPolycore -lPolycodeUI -lfreetype -lpng -lphysfs -lvorbisfile -lvorbis -logg -lportaudio -lasound -lz -lSDL -lGLEW -lGL -lX11 -lrt -llua -ldl
DLDFLAGSSTUDIO=-L$(LIBDIR) -pthread -lPolycored -lPolycodeUId -lfreetype -lpng -lphysfs -lvorbisfile -lvorbis -logg -lportaudio -lasound -lz -lSDL -lGLEW -lGL -lX11 -lrt -llua -ldl

default: setup core

all: setup core ui studio

debug: setup core_debug ui_debug studio_debug

setup:
	@mkdir -p $(LIBDIR)
	@mkdir -p Studio

.cpp.o:
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$<\033[0m]"
	@$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

.cpp.do:
	@echo "\033[1;32mBuilding Debug \033[0m[\033[1;33m$<\033[0m]"
	@$(CC) $(DEBUGFLAGS) $(CFLAGS) -c $< -o $@

.cpp.io:
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$<\033[0m]"
	@$(CC) $(CFLAGSSTUDIO) $(OPTFLAGS) -c $< -o $@

.cpp.dio:
	@echo "\033[1;32mBuilding Debug \033[0m[\033[1;33m$<\033[0m]"
	@$(CC) $(DEBUGFLAGS) $(CFLAGSSTUDIO) -c $< -o $@

core: $(OBJCORE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33m$(LIBDIR)/libPolycore.a\033[0m]"
	@ar rcs $(LIBDIR)/libPolycore.a $(OBJCORE)

core_debug: $(DOBJCORE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33m$(LIBDIR)/libPolycored.a\033[0m]"
	@ar rcs $(LIBDIR)/libPolycored.a $(DOBJCORE)

ui: $(OBJUI)
	@echo "\033[1;32mLinking \033[0m[\033[1;33m$(LIBDIR)/libPolycodeUI.a\033[0m]"
	@ar rcs $(LIBDIR)/libPolycodeUI.a $(OBJUI)

ui_debug: $(DOBJUI)
	@echo "\033[1;32mLinking \033[0m[\033[1;33m$(LIBDIR)/libPolycodeUId.a\033[0m]"
	@ar rcs $(LIBDIR)/libPolycodeUId.a $(DOBJUI)
	
template: core $(OBJTEMPLATE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33mTemplateApp/PolycodeTemplate\033[0m]"
	@$(CC) -o TemplateApp/PolycodeTemplate $(OBJTEMPLATE) $(LDFLAGSTEMPLATE) $(OPTFLAGS)
	@echo "\033[1;32mCopy Assets to: \033[0m[\033[1;33mTemplateApp\033[0m]"
	@cp $(ASSETDIR)/default/default.pak TemplateApp

template_debug: core_debug $(DOBJTEMPLATE)
	@echo "\033[1;32mLinking \033[0m[\033[1;33mTemplateApp/PolycodeTemplated\033[0m]"
	@$(CC) -o TemplateApp/PolycodeTemplated $(DOBJTEMPLATE) $(LDFLAGSTEMPLATE) $(DEBUGFLAGS)
	@echo "\033[1;32mCopy Assets to: \033[0m[\033[1;33mTemplateApp\033[0m]"
	@cp $(ASSETDIR)/default/default.pak TemplateApp

studio: core ui $(OBJSTUDIO)
	@echo "\033[1;32mLinking \033[0m[\033[1;33mStudio/Polycode\033[0m]"
	@$(CC) -o Studio/Polycode $(OBJSTUDIO) $(LDFLAGSSTUDIO) $(CFLAGSSTUDIO) $(OPTFLAGS)
	@echo "\033[1;32mCopy Assets to: \033[0m[\033[1;33mStudio\033[0m]"
	@cp -r $(ASSETDIR)/ide/* Studio
	@cp $(ASSETDIR)/default/default.pak Studio

studio_debug: core_debug ui_debug $(DOBJSTUDIO)
	@echo "\033[1;32mLinking \033[0m[\033[1;33mStudio/Polycoded\033[0m]"
	@$(CC) -o Studio/Polycoded $(DOBJSTUDIO) $(DLDFLAGSSTUDIO) $(CFLAGSSTUDIO) $(DEBUGFLAGS)
	@echo "\033[1;32mCopy Assets to: \033[0m[\033[1;33mStudio\033[0m]"
	@cp -r $(ASSETDIR)/ide/* Studio
	@cp $(ASSETDIR)/default/default.pak Studio

clean:
	rm -f $(OBJCORE) $(OBJUI) $(OBJTEMPLATE) $(OBJSTUDIO) $(DOBJCORE) $(DOBJUI) $(DOBJTEMPLATE) $(DOBJSTUDIO) $(LIBDIR)/libPolycore.a Studio/Polycode $(LIBDIR)/libPolycodeUI.a TemplateApp/PolycodeTemplate $(LIBDIR)/libPolycored.a Studio/Polycoded $(LIBDIR)/libPolycodeUId.a TemplateApp/PolycodeTemplated
