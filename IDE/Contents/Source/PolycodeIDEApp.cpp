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

PolycodeIDEApp::PolycodeIDEApp(SubstanceView *view) : EventDispatcher() {
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
	frame->getProjectBrowser()->addEventListener(this, PolycodeProjectBrowserEvent::SHOW_MENU);
	
	frame->Resize(core->getXRes(), core->getYRes());	
	core->setVideoMode(1000, 600, false, 0);
	
	
//	CoreServices::getInstance()->getResourceManager()->addArchive(RESOURCE_PATH"tomato.polyapp");
	
//	ScreenImage *img = new ScreenImage("tomato.png");
//	screen->addChild(img);
	
	loadConfigFile();
}

void PolycodeIDEApp::newProject() {
	frame->newProjectWindow->ResetForm();
	frame->showModal(frame->newProjectWindow);
	
}

void PolycodeIDEApp::newFile() {
	if(projectManager->getActiveProject()) {
		frame->newFileWindow->resetForm();
		frame->showModal(frame->newFileWindow);
	}
}

void PolycodeIDEApp::closeProject() {
	if(projectManager->getActiveProject()) {
		frame->getProjectBrowser()->removeProject(projectManager->getActiveProject());
		projectManager->removeProject(projectManager->getActiveProject());
	}
}

void PolycodeIDEApp::openProject() {
	
	vector<CoreFileExtension> extensions;
	CoreFileExtension ext;
	ext.extension = "polyproject";
	ext.description = "Polycode Project File";
	extensions.push_back(ext);
	vector<string> paths = core->openFilePicker(extensions, false);
	if(paths[0] != "") {
		PolycodeProject *project = projectManager->openProject(paths[0]);
		projectManager->setActiveProject(project);
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
		
		if(event->getEventType() == "PolycodeProjectBrowserEvent") {
			switch(event->getEventCode()) {
				case PolycodeProjectBrowserEvent::SHOW_MENU:
					dispatchEvent(new Event(), EVENT_SHOW_MENU);
				break;
			}
		}
		
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			BrowserUserData *selectedData = frame->getProjectBrowser()->getSelectedData();
			
			projectManager->setActiveProject(selectedData->parentProject);
			if(selectedData->type == 0)
				return;			
			
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

void PolycodeIDEApp::saveConfigFile() {
	Object configFile;
	configFile.root.name = "config";
	configFile.root.addChild("open_projects");
	for(int i=0; i < projectManager->getProjectCount(); i++) {
		PolycodeProject *project = projectManager->getProjectByIndex(i);		
		ObjectEntry *projectEntry = configFile.root["open_projects"]->addChild("project");
		projectEntry->addChild("name", project->getProjectName());
		projectEntry->addChild("path", project->getProjectFile());
	}
	core->createFolder("/Users/ivansafrin/Library/Application Support/Polycode");
	configFile.saveToXML("/Users/ivansafrin/Library/Application Support/Polycode/config.xml");		
}

void PolycodeIDEApp::loadConfigFile() {

	Object configFile;
	configFile.loadFromXML("/Users/ivansafrin/Library/Application Support/Polycode/config.xml");		
	if(configFile.root["open_projects"]) {
		ObjectEntry *projects = configFile.root["open_projects"];
		if(projects) {
		for(int i=0; i < projects->length; i++) {
			ObjectEntry *entry = (*(*projects)[i])["path"];
			if(entry) {
				projectManager->openProject(entry->stringVal);	
			}
		}
		}
	}
}


PolycodeIDEApp::~PolycodeIDEApp() {
	
	saveConfigFile();
	
	delete core;
}

bool PolycodeIDEApp::Update() {
	return core->Update();
}

