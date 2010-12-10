/*
 *  PolycodeIDEApp.cpp
 *  Polycode
 *
 *  Created by Ivan Safrin on 11/29/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */


#include "PolycodeIDEApp.h"


using namespace Polycode;

PolycodeIDEApp::PolycodeIDEApp(SubstanceView *view) : EventHandler() {
	core = new CocoaCore(view, 800,600,false,0,60);	
	core->addEventListener(this, Core::EVENT_CORE_RESIZE);	
	CoreServices::getInstance()->getRenderer()->setClearColor(0.4,0.4,0.4);
		
	CoreServices::getInstance()->getConfig()->loadConfig("Polycode", RESOURCE_PATH"UIThemes/default/theme.xml");
	CoreServices::getInstance()->getResourceManager()->addDirResource(RESOURCE_PATH"UIThemes/default/", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource(RESOURCE_PATH"Images/", false);
	
//	CoreServices::getInstance()->getFontManager()->registerFont("sans", RESOURCE_PATH"Fonts/DejaVuSans.ttf");
//	CoreServices::getInstance()->getFontManager()->registerFont("mono", RESOURCE_PATH"Fonts/DejaVuSansMono.ttf");	
	CoreServices::getInstance()->getFontManager()->registerFont("sans",  "/System/Library/Fonts/LucidaGrande.ttc");	
	CoreServices::getInstance()->getFontManager()->registerFont("mono", "/System/Library/Fonts/Monaco.dfont");	
	
	printf("creating font editor\n"); 
	
	Screen *screen = new Screen();	
	
	editorManager = new PolycodeEditorManager();
	
	editorManager->registerEditorFactory(new PolycodeImageEditorFactory());
	editorManager->registerEditorFactory(new PolycodeFontEditorFactory());
	editorManager->registerEditorFactory(new PolycodeTextEditorFactory());
	
	frame = new PolycodeFrame();
	frame->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	
	frame->newProjectWindow->addEventListener(this, UIEvent::OK_EVENT);
	
	screen->addChild(frame);
	
	projectManager = new PolycodeProjectManager();
	projectManager->setProjectBrowser(frame->getProjectBrowser());
	
	frame->getProjectBrowser()->addEventListener(this, Event::CHANGE_EVENT);
	
	frame->Resize(core->getXRes(), core->getYRes());	
	core->setVideoMode(1000, 600, false, 0);
	
}

void PolycodeIDEApp::newProject() {
	frame->newProjectWindow->ResetForm();
	frame->showModal(frame->newProjectWindow);
}

void PolycodeIDEApp::openProject() {
	
	vector<CoreFileExtension> extensions;
	CoreFileExtension ext;
	ext.extension = "polyproject";
	ext.description = "Polycode Project File";
	extensions.push_back(ext);
	vector<string> paths = core->openFilePicker(extensions, false);
	if(paths[0] != "") {
		projectManager->openProject(paths[0]);
	}
}

void PolycodeIDEApp::saveFile() {
	editorManager->getCurrentEditor()->saveFile();
}

void PolycodeIDEApp::handleEvent(Event *event) {
	if(event->getDispatcher() == core) {
		switch(event->getEventCode()) {
			case Core::EVENT_CORE_RESIZE:
				frame->Resize(core->getXRes(), core->getYRes());
			break;
		}
	}
	
	if(event->getDispatcher()  == frame->getProjectBrowser()) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			BrowserUserData *selectedData = frame->getProjectBrowser()->getSelectedData();
			
			if(selectedData) {
			PolycodeEditor *editor;
			editor = editorManager->getEditorForPath(selectedData->fileEntry.fullPath);
			if(editor) {
				frame->showEditor(editor);				
			} else {
				editor = editorManager->createEditorForExtension(selectedData->fileEntry.extension);
				if(editor) {
					if(editor->openFile(selectedData->fileEntry.fullPath)) {
						frame->addEditor(editor);					
						frame->showEditor(editor);
					} else {
						delete editor;
						editor = NULL;
					}
				}
			}
				
				if(editor) {
					editorManager->setCurrentEditor(editor);
				}
				
			}
		}
	}	
	
	if(event->getDispatcher() == frame->newProjectWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->createNewProject(frame->newProjectWindow->getTemplateFolder(), frame->newProjectWindow->getProjectName(), frame->newProjectWindow->getProjectLocation());
			frame->hideModal();			
		}
	}
}

PolycodeIDEApp::~PolycodeIDEApp() {
	delete core;
}

bool PolycodeIDEApp::Update() {
	return core->Update();
}

