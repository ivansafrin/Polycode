/*
 Copyright (C) 2012 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolycodeIDEApp.h"


using namespace Polycode;

UIGlobalMenu *globalMenu;
SyntaxHighlightTheme *globalSyntaxTheme;

PolycodeIDEApp::PolycodeIDEApp(PolycodeView *view) : EventDispatcher() {
	core = new CocoaCore(view, 900,700,false,true, 0, 0,30);	
	core->addEventListener(this, Core::EVENT_CORE_RESIZE);	
	CoreServices::getInstance()->getRenderer()->setClearColor(0.2,0.2,0.2);
	
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
				
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");	

	CoreServices::getInstance()->getResourceManager()->addArchive("hdr.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("hdr");	


	CoreServices::getInstance()->getResourceManager()->addArchive("api.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("Physics2D.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("Physics3D.pak");
	CoreServices::getInstance()->getResourceManager()->addArchive("UI.pak");
			
	CoreServices::getInstance()->getConfig()->loadConfig("Polycode", "UIThemes/default/theme.xml");
	CoreServices::getInstance()->getResourceManager()->addArchive("UIThemes/default/");
	CoreServices::getInstance()->getResourceManager()->addArchive("Images/");	

	CoreServices::getInstance()->getFontManager()->registerFont("section", "Fonts/LeagueGothic-Regular.otf");	

	CoreServices::getInstance()->getFontManager()->registerFont("editor_font", "Fonts/Inconsolata.otf");

//	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_LINEAR);
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	
	willRunProject = false;

		
	printf("creating font editor\n"); 
	
	Screen *screen = new Screen();	
	screen->rootEntity.setDefaultScreenOptions(true);
	
	editorManager = new PolycodeEditorManager();
	
	frame = new PolycodeFrame();
	frame->setPositionMode(ScreenEntity::POSITION_TOPLEFT);

	frame->console->backtraceWindow->addEventListener(this, BackTraceEvent::EVENT_BACKTRACE_SELECTED);

	frame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);	
	frame->yesNoPopup->addEventListener(this, UIEvent::OK_EVENT);
	
	frame->newProjectWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->exportProjectWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->newFileWindow->addEventListener(this, UIEvent::OK_EVENT);	
	frame->exampleBrowserWindow->addEventListener(this, UIEvent::OK_EVENT);
	
	frame->playButton->addEventListener(this, UIEvent::CLICK_EVENT);
	frame->stopButton->addEventListener(this, UIEvent::CLICK_EVENT);

	screen->addChild(frame);

	
	projectManager = new PolycodeProjectManager();
	projectManager->setProjectBrowser(frame->getProjectBrowser());
	
	frame->projectManager = projectManager;
	
	frame->getProjectBrowser()->addEventListener(this, Event::CHANGE_EVENT);
	frame->getProjectBrowser()->addEventListener(this, PolycodeProjectBrowserEvent::HANDLE_MENU_COMMAND);
	
	frame->Resize(core->getXRes(), core->getYRes());	
	core->setVideoMode(1100, 700, false, false, 0, 0);
	
	debugger = new PolycodeRemoteDebugger(projectManager);
	frame->console->setDebugger(debugger);
	
	editorManager->registerEditorFactory(new PolycodeImageEditorFactory());
	editorManager->registerEditorFactory(new PolycodeMaterialEditorFactory());	
	editorManager->registerEditorFactory(new PolycodeScreenEditorFactory());	
	editorManager->registerEditorFactory(new PolycodeFontEditorFactory());
	editorManager->registerEditorFactory(new PolycodeTextEditorFactory());
	editorManager->registerEditorFactory(new PolycodeProjectEditorFactory(projectManager));
	editorManager->registerEditorFactory(new PolycodeSpriteEditorFactory());

		
	globalMenu	= new UIGlobalMenu();
	screen->addChild(globalMenu);	
				
	loadConfigFile();
	frame->console->applyTheme();
}

void PolycodeIDEApp::renameFile() {
	if(projectManager->selectedFile != "") {
		frame->textInputPopup->action = "renameFile";
		frame->textInputPopup->setCaption("Enter new filename");
		frame->textInputPopup->setValue(projectManager->selectedFileEntry.name);
		frame->showModal(frame->textInputPopup);
	}
}

void PolycodeIDEApp::doRemoveFile() {
	if(projectManager->selectedFile != "") {
		core->removeDiskItem(projectManager->selectedFile);
		if(projectManager->getActiveProject()) {
			frame->projectBrowser->refreshProject(projectManager->getActiveProject());
		}
	}
}

void PolycodeIDEApp::removeFile() {
	if(projectManager->selectedFile != "") {
		frame->yesNoPopup->setCaption("Are you sure you want to remove this file?");
		frame->yesNoPopup->action = "removeFile";
		frame->showModal(frame->yesNoPopup);
	}
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

void PolycodeIDEApp::refreshProject() {
	if(projectManager->getActiveProject()) {
		frame->getProjectBrowser()->refreshProject(projectManager->getActiveProject());
	}
}

void PolycodeIDEApp::closeProject() {
	if(projectManager->getActiveProject()) {
		frame->getProjectBrowser()->removeProject(projectManager->getActiveProject());
		projectManager->removeProject(projectManager->getActiveProject());
	}
}

void PolycodeIDEApp::newGroup() {
	if(projectManager->activeFolder != "") {
		frame->textInputPopup->action = "newGroup";
		frame->textInputPopup->setCaption("New folder name");
		frame->textInputPopup->setValue("New Folder");
		frame->showModal(frame->textInputPopup);	
	}
}

void PolycodeIDEApp::openProject() {
	
	vector<CoreFileExtension> extensions;
	CoreFileExtension ext;
	ext.extension = "polyproject";
	ext.description = "Polycode Project File";
	extensions.push_back(ext);
	std::vector<String> paths = core->openFilePicker(extensions, false);
	if(paths.size() == 0) 
		return;
	if(paths[0] != "") {
		PolycodeProject *project = projectManager->openProject(paths[0]);
		if(project) {
			projectManager->setActiveProject(project);
			OSFileEntry projectEntry =  OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
			openFile(projectEntry);			
		}
	}		
}

void PolycodeIDEApp::browseExamples() {
	frame->newProjectWindow->ResetForm();
	frame->showModal(frame->exampleBrowserWindow);

}

void PolycodeIDEApp::stopProject() {
	printf("Disconnecting clients...\n");
	if(debugger->isConnected()) {
		debugger->Disconnect();
	}
}

void PolycodeIDEApp::exportProject() {
	if(projectManager->getActiveProject()) {
		frame->exportProjectWindow->resetForm();
		frame->showModal(frame->exportProjectWindow);		
	}	
}

void PolycodeIDEApp::runProject() {
	printf("Running project...\n");
	stopProject();

	if(projectManager->getActiveProject()) {
		String outPath = PolycodeToolLauncher::generateTempPath(projectManager->getActiveProject()) + ".polyapp";
		PolycodeToolLauncher::buildProject(projectManager->getActiveProject(), outPath);
		PolycodeToolLauncher::runPolyapp(outPath);
	} else {
		PolycodeConsole::print("No active project!\n");
	}
}

void PolycodeIDEApp::addFiles() {
	if(projectManager->getActiveProject()) {	
		vector<CoreFileExtension> extensions;		
		std::vector<String> files = core->openFilePicker(extensions, true);				
		
		for(int i=0; i < files.size(); i++) {
			OSFileEntry entry = OSFileEntry(files[i], OSFileEntry::TYPE_FILE);
			core->copyDiskItem(files[i], projectManager->activeFolder + "/" + entry.name);
		}
		
		frame->getProjectBrowser()->refreshProject(projectManager->getActiveProject());		
	}			
}

void PolycodeIDEApp::findText() {
	if(editorManager->getCurrentEditor()) {
		if(editorManager->getCurrentEditor()->getEditorType() == "PolycodeTextEditor") {
			PolycodeTextEditor *textEditor = (PolycodeTextEditor*) editorManager->getCurrentEditor();
			textEditor->showFindBar();
		}
	}
}

void PolycodeIDEApp::saveFile() {
	if(editorManager->getCurrentEditor()) {
		editorManager->getCurrentEditor()->saveFile();
	}
}

void PolycodeIDEApp::openProject(String projectFile) {
	projectManager->openProject(projectFile);
}

void PolycodeIDEApp::openDocs() {

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
	String docsURL = "file://localhost"+polycodeBasePath+"/Standalone/Docs/html/index.html";
	core->openURL(docsURL);
}

void PolycodeIDEApp::openFileInProject(PolycodeProject *project, String filePath) {
	OSFileEntry fileEntry = OSFileEntry(project->getRootFolder()+"/"+filePath, OSFileEntry::TYPE_FILE);	
	OSFILE *file = OSBasics::open(project->getRootFolder()+"/"+filePath,"r");
	
	if(file) {
		OSBasics::close(file);
		openFile(fileEntry);		
	} else {
		fileEntry = OSFileEntry(filePath, OSFileEntry::TYPE_FILE);	
		file = OSBasics::open(filePath,"r");	
		if(file) {
			OSBasics::close(file);
			openFile(fileEntry);							
		} else {
			PolycodeConsole::print("File not available.\n");
		}
	}

}

void PolycodeIDEApp::openFile(OSFileEntry file) {
	PolycodeEditor *editor;
	editor = editorManager->getEditorForPath(file.fullPath);
	if(editor) {
		frame->showEditor(editor);
	} else {
		editor = editorManager->createEditorForExtension(file.extension);
		if(editor) {
			editor->parentProject = projectManager->getActiveProject();
			if(editor->openFile(file)) {
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

void PolycodeIDEApp::handleEvent(Event *event) {

	if(event->getDispatcher() == frame->console->backtraceWindow) {
		if(event->getEventType() == "BackTraceEvent" && event->getEventCode() == BackTraceEvent::EVENT_BACKTRACE_SELECTED) {
			BackTraceEvent *btEvent = (BackTraceEvent*) event;
			openFileInProject(btEvent->project, btEvent->fileName);
			
			PolycodeEditor *editor = editorManager->getCurrentEditor();
			if(editor) {
				if(editor->getEditorType() == "PolycodeTextEditor") {
					PolycodeTextEditor *textEditor = (PolycodeTextEditor*) editor;
					textEditor->highlightLine(btEvent->lineNumber);
				}
				
			}	
		}
	}

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
				case PolycodeProjectBrowserEvent::HANDLE_MENU_COMMAND:
					PolycodeProjectBrowserEvent *bEvent = (PolycodeProjectBrowserEvent*) event;
					
					if(bEvent->command == "add_new_file") {					
						newFile();
					} else if(bEvent->command == "add_files") {
						addFiles();
					} else if(bEvent->command == "add_new_project") {
						newProject();
					} else if(bEvent->command == "add_new_folder") {				
						newGroup();
					} else if(bEvent->command == "refresh") {
						refreshProject();
					} else if(bEvent->command == "rename") {
						renameFile();
					} else if(bEvent->command == "remove") {
						removeFile();
					}																				
				break;
			}
		}
		
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			BrowserUserData *selectedData = frame->getProjectBrowser()->getSelectedData();
						
			if(selectedData->type == 3) {
				projectManager->activeFolder = selectedData->parentProject->getRootFolder();
				projectManager->selectedFile = "";				
			} else if(selectedData->type == 0) {
				projectManager->activeFolder = "";
				projectManager->selectedFile = "";
			} else {
				projectManager->selectedFileEntry = selectedData->fileEntry;
				projectManager->selectedFile = selectedData->fileEntry.fullPath;
				if(selectedData->fileEntry.type == OSFileEntry::TYPE_FILE) {
					projectManager->activeFolder = selectedData->fileEntry.basePath;
				} else {
					projectManager->activeFolder = selectedData->fileEntry.fullPath;
				}			
			}
			
			projectManager->setActiveProject(selectedData->parentProject);
			
			if(selectedData->type == 0)
				return;			
			
			if(selectedData) {
				openFile(selectedData->fileEntry);
			}
		}
	}
	
	if(event->getDispatcher() == frame->playButton) {	
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			willRunProject = true;
		}
	}

	if(event->getDispatcher() == frame->stopButton) {	
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			stopProject();
		}
	}

	if(event->getDispatcher() == frame->yesNoPopup) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			if(frame->yesNoPopup->action == "removeFile") {
				doRemoveFile();
			}
			frame->hideModal();
			frame->yesNoPopup->action = "";
		}
	}
	
	if(event->getDispatcher() == frame->textInputPopup) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
						
			if(frame->textInputPopup->action == "newGroup") {	
				core->createFolder(projectManager->activeFolder+"/"+frame->textInputPopup->getValue());
				if(projectManager->getActiveProject()) {
					frame->getProjectBrowser()->refreshProject(projectManager->getActiveProject());
				}			
			}
			
			if(frame->textInputPopup->action == "renameFile") {		
				core->moveDiskItem(projectManager->selectedFileEntry.fullPath, projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue());			
				if(projectManager->getActiveProject()) {
					frame->getProjectBrowser()->refreshProject(projectManager->getActiveProject());
				}
				
				PolycodeEditor *editor = editorManager->getEditorForPath(projectManager->selectedFileEntry.fullPath);
				if(editor) {
					editor->setFilePath(projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue());
				}
				
				projectManager->selectedFileEntry.fullPath = projectManager->selectedFileEntry.basePath + "/" + frame->textInputPopup->getValue();
				projectManager->selectedFileEntry.name = frame->textInputPopup->getValue();				
			}
			
			frame->hideModal();			
		}
	}	

	if(event->getDispatcher() == frame->exportProjectWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->exportProject(projectManager->getActiveProject(), frame->exportProjectWindow->projectLocationInput->getText(), frame->exportProjectWindow->macCheckBox->isChecked(), frame->exportProjectWindow->winCheckBox->isChecked(), frame->exportProjectWindow->linCheckBox->isChecked());
			frame->hideModal();			
		}
	}

	
	if(event->getDispatcher() == frame->newProjectWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->createNewProject(frame->newProjectWindow->getTemplateFolder(), frame->newProjectWindow->getProjectName(), frame->newProjectWindow->getProjectLocation());
			frame->hideModal();			
		}
	}

	if(event->getDispatcher() == frame->newFileWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			projectManager->createNewFile(frame->newFileWindow->getTemplatePath(), frame->newFileWindow->getFileName());
			frame->hideModal();			
			
			if(projectManager->getActiveProject()) {
				frame->projectBrowser->refreshProject(projectManager->getActiveProject());
			}			
		}
	}
	
	if(event->getDispatcher() == frame->exampleBrowserWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			String fullPath = String(core->getDefaultWorkingDirectory()+"/"+frame->exampleBrowserWindow->getExamplePath());
			PolycodeProject* project = projectManager->openProject(fullPath);
			OSFileEntry projectEntry =  OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
			projectManager->setActiveProject(project);
			openFile(projectEntry);			
			
			frame->hideModal();			
		}
	}	
}

void PolycodeIDEApp::saveConfigFile() {
	Object configFile;
	configFile.root.name = "config";
	configFile.root.addChild("open_projects");
	configFile.root.addChild("syntax_theme", globalSyntaxTheme->name);
	for(int i=0; i < projectManager->getProjectCount(); i++) {
		PolycodeProject *project = projectManager->getProjectByIndex(i);		
		ObjectEntry *projectEntry = configFile.root["open_projects"]->addChild("project");
		projectEntry->addChild("name", project->getProjectName());
		projectEntry->addChild("path", project->getProjectFile());
	}
	core->createFolder(core->getUserHomeDirectory()+"/Library/Application Support/Polycode");
	configFile.saveToXML(core->getUserHomeDirectory()+"/Library/Application Support/Polycode/config.xml");	
}

void PolycodeIDEApp::loadConfigFile() {
	Object configFile;
	// TODO: Make a crossplatform core method to get application data path
	configFile.loadFromXML(core->getUserHomeDirectory()+"/Library/Application Support/Polycode/config.xml");
		
	globalSyntaxTheme = new SyntaxHighlightTheme();
	String themeName = "default";
	ObjectEntry *syntaxTheme = configFile.root["syntax_theme"];
	if(syntaxTheme) {
		themeName = syntaxTheme->stringVal;
	}
	themeName = "monokai";	
	globalSyntaxTheme->loadFromFile(themeName);
	
	if(configFile.root["open_projects"]) {
		ObjectEntry *projects = configFile.root["open_projects"];
		if(projects) {
		for(int i=0; i < projects->length; i++) {
			ObjectEntry *entry = (*(*projects)[i])["path"];
			if(entry) {
				PolycodeProject* project = projectManager->openProject(entry->stringVal);
				OSFileEntry projectEntry =  OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
				projectManager->setActiveProject(project);
				openFile(projectEntry);
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

	if(willRunProject) {
		willRunProject = false;
		runProject();
	}

	if(debugger->isConnected()) {
			frame->stopButton->visible = true;
			frame->stopButton->enabled = true;			
			
			frame->playButton->visible = false;
			frame->playButton->enabled = false;			
			
	} else {
			frame->stopButton->visible = false;
			frame->stopButton->enabled = false;			
			
			frame->playButton->visible = true;
			frame->playButton->enabled = true;				
	}

	if(projectManager->getProjectCount() == 1) {
		projectManager->setActiveProject(projectManager->getProjectByIndex(0));
	}
	
	if(projectManager->getProjectCount() > 0) {
		frame->welcomeEntity->enabled =  false;
		frame->projectBrowser->enabled =  true;		
		frame->mainSizer->enabled = true;
	} else {
		frame->welcomeEntity->enabled =  true;
		frame->projectBrowser->enabled =  false;			
		frame->mainSizer->enabled = false;		
	}

	return core->Update();
}

