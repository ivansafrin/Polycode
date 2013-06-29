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
PolycodeClipboard *globalClipboard;


PolycodeIDEApp::PolycodeIDEApp(PolycodeView *view) : EventDispatcher() {
	core = new POLYCODE_CORE(view, 1100, 700,false,true, 0, 0,30, -1);
//	core->pauseOnLoseFocus = true;

	CoreServices::getInstance()->getResourceManager()->reloadResourcesOnModify = true;

	runNextFrame = false;

	core->addEventListener(this, Core::EVENT_CORE_RESIZE);
	core->addEventListener(this, Core::EVENT_LOST_FOCUS);
	core->addEventListener(this, Core::EVENT_GAINED_FOCUS);

	globalClipboard = new PolycodeClipboard();

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

	CoreServices::getInstance()->getFontManager()->registerFont("section", "Fonts/Roboto-Thin.ttf");

	CoreServices::getInstance()->getRenderer()->clearColor.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiBgColor"));

//	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_LINEAR);
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);

	willRunProject = false;

	globalMenu = new UIGlobalMenu();

	printf("creating font editor\n"); 

	Screen *screen = new Screen();
	screen->rootEntity.setDefaultScreenOptions(true);

	editorManager = new PolycodeEditorManager();

	frame = new PolycodeFrame();
	frame->setPositionMode(ScreenEntity::POSITION_TOPLEFT);

	frame->editorManager = editorManager;
	editorManager->addEventListener(frame, Event::CHANGE_EVENT);

	frame->console->backtraceWindow->addEventListener(this, BackTraceEvent::EVENT_BACKTRACE_SELECTED);

	frame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);

	frame->yesNoPopup->addEventListener(this, UIEvent::OK_EVENT);
	frame->yesNoPopup->addEventListener(this, UIEvent::CANCEL_EVENT);

	frame->yesNoCancelPopup->addEventListener(this, UIEvent::YES_EVENT);
	frame->yesNoCancelPopup->addEventListener(this, UIEvent::NO_EVENT);


	frame->newProjectWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->exportProjectWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->newFileWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->exampleBrowserWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->settingsWindow->addEventListener(this, UIEvent::OK_EVENT);
	frame->settingsWindow->addEventListener(this, UIEvent::CLOSE_EVENT);

	frame->playButton->addEventListener(this, UIEvent::CLICK_EVENT);
	frame->stopButton->addEventListener(this, UIEvent::CLICK_EVENT);

	screen->addChild(frame);


	projectManager = new PolycodeProjectManager();
	projectManager->setProjectBrowser(frame->getProjectBrowser());

	frame->projectManager = projectManager;

	projectManager->addEventListener(frame, Event::CHANGE_EVENT);

	frame->getProjectBrowser()->addEventListener(this, Event::CHANGE_EVENT);
	frame->getProjectBrowser()->addEventListener(this, PolycodeProjectBrowserEvent::HANDLE_MENU_COMMAND);

	frame->Resize(core->getXRes(), core->getYRes());


	debugger = new PolycodeRemoteDebugger(projectManager);
	frame->console->setDebugger(debugger);

	editorManager->registerEditorFactory(new PolycodeImageEditorFactory());
	editorManager->registerEditorFactory(new PolycodeMaterialEditorFactory());
	editorManager->registerEditorFactory(new PolycodeScreenEditorFactory());
	editorManager->registerEditorFactory(new PolycodeFontEditorFactory());
	editorManager->registerEditorFactory(new PolycodeTextEditorFactory());
	editorManager->registerEditorFactory(new PolycodeProjectEditorFactory(projectManager));
	editorManager->registerEditorFactory(new PolycodeSpriteEditorFactory());


	screen->addChild(globalMenu);

	loadConfigFile();
	frame->console->applyTheme();

#ifdef USE_POLYCODEUI_MENUBAR
	menuBar = new UIMenuBar(100, globalMenu);

	UIMenuBarEntry *fileEntry = menuBar->addMenuBarEntry("File");
	fileEntry->addItem("New File", "new_file", KEY_n);
	fileEntry->addItem("New Project", "new_project", KEY_LSHIFT, KEY_n);
	fileEntry->addItem("New Folder", "new_folder", KEY_LSHIFT, KEY_f);
	fileEntry->addItem("Open Project", "open_project", KEY_LSHIFT, KEY_o);
	fileEntry->addItem("Close Project", "close_project", KEY_LSHIFT, KEY_w);
	fileEntry->addItem("Close File", "close_file", KEY_w);
	fileEntry->addItem("Remove File", "remove_file");
	fileEntry->addItem("Refresh Project", "refresh_project");
	fileEntry->addItem("Save File", "save_file", KEY_s);
	fileEntry->addItem("Browse Examples", "browse_examples", KEY_LSHIFT, KEY_e);
	fileEntry->addItem("Quit", "quit");

	UIMenuBarEntry *editEntry = menuBar->addMenuBarEntry("Edit");
	editEntry->addItem("Undo", "undo");
	editEntry->addItem("Redo", "redo");
	editEntry->addItem("Cut", "cut");
	editEntry->addItem("Copy", "copy");
	editEntry->addItem("Settings", "settings");

	UIMenuBarEntry *viewEntry = menuBar->addMenuBarEntry("View");
	viewEntry->addItem("Toggle Console", "toggle_console", KEY_LSHIFT, KEY_c);

	UIMenuBarEntry *projectEntry = menuBar->addMenuBarEntry("Project");
	projectEntry->addItem("Run Project", "run_project", KEY_r);
	projectEntry->addItem("Publish Project", "export_project");

	UIMenuBarEntry *helpEntry = menuBar->addMenuBarEntry("Help");
	helpEntry->addItem("API Reference", "show_api");
	helpEntry->addItem("About Polycode", "show_about");


	menuBar->addEventListener(this, UIEvent::OK_EVENT);

	screen->addChild(menuBar);
	frame->position.y = 25;
#else
	menuBar = NULL;
#endif
	core->setVideoMode(1100, 700, false, true, 0, 0);

	needsRedraw = false;
	lastConnected = false;

	frame->closeFileButton->addEventListener(this, UIEvent::CLICK_EVENT);

	quittingApp = false;

	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void PolycodeIDEApp::renameFile() {
	if(projectManager->selectedFile != "") {
		frame->textInputPopup->action = "renameFile";
		frame->textInputPopup->setCaption("Enter new filename");
		frame->textInputPopup->setValue(projectManager->selectedFileEntry.name);
		frame->showModal(frame->textInputPopup);
	}
}

void PolycodeIDEApp::showAbout() {
	frame->showModal(frame->aboutWindow);
}

void PolycodeIDEApp::showSettings() {
	frame->showModal(frame->settingsWindow);
}

void PolycodeIDEApp::toggleConsole() {
	frame->toggleConsole();
}

void PolycodeIDEApp::doRemoveFile() {
	if(projectManager->selectedFile != "") {
		core->removeDiskItem(projectManager->selectedFile);
		if(projectManager->getActiveProject()) {
			frame->projectBrowser->refreshProject(projectManager->getActiveProject());
		}
		PolycodeEditor *editor;
		for (int i=0; i < editorManager->openEditors.size(); i++) {
			if (editorManager->openEditors[i]->getFilePath() == projectManager->selectedFile) {
				editor = editorManager->openEditors[i];
				break;
			}
		}
		// have to set changes to false to avoid problems with saving and modal dialogs in removeEditor()
		// besides, we're removing the file, so saving is not necessary
		if (editor) {
			editor->setHasChanges(false);
			removeEditor(editor);
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

// check if associated file has changes before invoking this
void PolycodeIDEApp::removeEditor(PolycodeEditor *editor) {
	if (!editor)
		return;

	frame->removeEditor(editor);
	editorManager->destroyEditor(editor);
	if(editorManager->openEditors.size() > 0) {
		editorManager->setCurrentEditor(editorManager->openEditors[0]);
		frame->showEditor(editorManager->openEditors[0]);
	} else {
		editorManager->setCurrentEditor(NULL);
	}
}

void PolycodeIDEApp::closeFile() {
	// this will save the file if it has changes and/or close it (in closeFiles())
	PolycodeEditor *editor = editorManager->getCurrentEditor();
	if (editor) {
		std::vector<PolycodeEditor*> editorToSave;
		editorToSave.push_back(editor);
		OSFileEntry entry(editor->getFilePath(), OSFileEntry::TYPE_FILE);
		closeFiles(editorToSave, "'"+entry.name+"' has unsaved changes. Save?");
	}
}

void PolycodeIDEApp::closeFiles(std::vector<PolycodeEditor*> editors, String saveMsg) {
	if (filesHaveChanges(editors)) {
		if (saveMsg == "")
			saveMsg = "File(s) have unsaved changes. Save all?";
		tempEditorStore = editors;
		frame->yesNoCancelPopup->setCaption(saveMsg);
		frame->yesNoCancelPopup->action = "closeFiles";
		frame->showModal(frame->yesNoCancelPopup);
	} else
		doCloseFiles(editors);
}

void PolycodeIDEApp::doCloseFiles(std::vector<PolycodeEditor*> editors) {
	for (int i=0; i < editors.size(); i++) {
		if (editors[i])
			removeEditor(editors[i]);
	}
}

void PolycodeIDEApp::closeProject() {
	if(projectManager->getActiveProject()) {
		std::vector<PolycodeEditor*> editors;
		PolycodeEditor *editor;
		bool hasChanges = false;
		for (int i=0; i < editorManager->openEditors.size(); i++) {
			editor = editorManager->openEditors[i];
			if (editor->hasChanges())
				hasChanges = true;
			if (editor->parentProject == projectManager->getActiveProject())
				editors.push_back(editor);
		}
		tempEditorStore = editors; // current project files
		if (hasChanges) {
			String name = projectManager->getActiveProject()->getProjectName();
			frame->yesNoCancelPopup->setCaption("Project '" + name + "' has unsaved changes. Save all?");
			frame->yesNoCancelPopup->action = "closeProject";
			frame->showModal(frame->yesNoCancelPopup);
		} else
			doCloseProject();
	} else
		PolycodeConsole::print("There are no active projects to close.\n");
}

// private helper function that removes editors and project on project close.
void PolycodeIDEApp::doCloseProject() {
	doCloseFiles(tempEditorStore);
	frame->getProjectBrowser()->removeProject(projectManager->getActiveProject());
	projectManager->removeProject(projectManager->getActiveProject());
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

#ifdef USE_POLYCODEUI_FILE_DIALOGS
	std::vector<String> exts;
	exts.push_back("polyproject");
	frame->showFileBrowser(CoreServices::getInstance()->getCore()->getUserHomeDirectory(),	false, exts, false);
	frame->fileDialog->addEventListener(this, UIEvent::OK_EVENT);
#else
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
			OSFileEntry projectEntry = OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
			openFile(projectEntry);
		}
	}
#endif
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

void PolycodeIDEApp::doRunProject() {
	printf("Running project...\n");
	stopProject();

	frame->showConsole();

	String outPath = PolycodeToolLauncher::generateTempPath(projectManager->getActiveProject()) + ".polyapp";
	PolycodeToolLauncher::buildProject(projectManager->getActiveProject(), outPath, false);
	PolycodeToolLauncher::runPolyapp(outPath);
}

bool PolycodeIDEApp::quitApp() {

	quittingApp = true;

	while(editorManager->getCurrentEditor()) {
		PolycodeEditor *editor = editorManager->getCurrentEditor();
		
		if(editor->hasChanges()) {
			OSFileEntry entry(editor->getFilePath(), OSFileEntry::TYPE_FILE);
			frame->yesNoCancelPopup->setCaption("The file \""+entry.name+"\" has unsaved changes. Save before quitting?");
			frame->yesNoCancelPopup->action = "closeQuitFile";
			frame->showModal(frame->yesNoCancelPopup);
			return false;
		} else {
			frame->removeEditor(editor);
			editorManager->destroyEditor(editor);
			if(editorManager->openEditors.size() > 0) {
				editorManager->setCurrentEditor(editorManager->openEditors[0]);
				frame->showEditor(editorManager->openEditors[0]);
			} else{
				editorManager->setCurrentEditor(NULL);
			}
		}

	}

	return true;
}

void PolycodeIDEApp::runProject() {
	if(projectManager->getActiveProject()) {
		if(editorManager->hasUnsavedFilesForProject(projectManager->getActiveProject())) {
			frame->yesNoPopup->setCaption("This project has unsaved files. Save before building?");
			frame->yesNoPopup->action = "saveAndRun";
			frame->showModal(frame->yesNoPopup);
		} else {
			doRunProject();
		}
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
	if(editorManager->getCurrentEditor() && editorManager->getCurrentEditor()->getEditorType() == "PolycodeTextEditor") {
		PolycodeTextEditor *textEditor = (PolycodeTextEditor*) editorManager->getCurrentEditor();
		textEditor->showFindBar();
	}
}

void PolycodeIDEApp::saveFile() {
	if(editorManager->getCurrentEditor()) {
		editorManager->getCurrentEditor()->saveFile();
	}
}

void PolycodeIDEApp::saveFiles(std::vector<PolycodeEditor*> editors) {
	for (int i=0; i < editors.size(); i++) {
		if (editors[i]->hasChanges())
			editors[i]->saveFile();
	}
}

bool PolycodeIDEApp::filesHaveChanges(std::vector<PolycodeEditor*> editors) {
	for (int i=0; i < editors.size(); i++) {
		if (editors[i]->hasChanges())
			return true;
	}
	return false;
}

void PolycodeIDEApp::openProject(String projectFile) {
	projectManager->openProject(projectFile);
}

void PolycodeIDEApp::openDocs() {

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
#if defined(__APPLE__) && defined(__MACH__)
	String docsURL = "file://localhost"+polycodeBasePath+"/Standalone/Docs/html/index.html";
	core->openURL(docsURL);
#else
	String docsURL = polycodeBasePath+"/Standalone/Docs/html/index.html";
	printf("Opening %s\n", docsURL.c_str());
	core->openURL(docsURL);
#endif
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

	PolycodeEditorFactory *factory = editorManager->getEditorFactoryForExtension(file.extension);
	if(dynamic_cast<PolycodeTextEditorFactory*>(factory)) {
		CoreServices *core = CoreServices::getInstance();
		Config *config = core->getConfig();
		bool useExternalTextEditor = (config->getStringValue("Polycode", "useExternalTextEditor") == "true") && (config->getStringValue("Polycode", "externalTextEditorCommand") != "");

		if(useExternalTextEditor) {
			PolycodeToolLauncher::openExternalEditor(config->getStringValue("Polycode", "externalTextEditorCommand"), file.fullPath, projectManager->getActiveProject()->getRootFolder());
			return;
		}
	}

	PolycodeEditor *editor = editorManager->getEditorForPath(file.fullPath);

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

	if(event->getDispatcher() == frame->fileDialog && event->getEventCode() == UIEvent::OK_EVENT && event->getEventType() == "UIEvent") {
		String path = frame->fileDialog->getSelection();
		if(path != "") {
			PolycodeProject *project = projectManager->openProject(path);
			if(project) {
				projectManager->setActiveProject(project);
				OSFileEntry projectEntry = OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
				openFile(projectEntry);
			}

		}
	}

	if(event->getDispatcher() == menuBar) {
		String action = menuBar->getSelectedItem();

		if(action == "new_file") {
			newFile();
		} else if(action == "new_project") {
			newProject();
		} else if(action == "new_folder") {
			newGroup();
		} else if(action == "open_project") {
			openProject();
		} else if(action == "close_project") {
			closeProject();
		} else if(action == "close_file") {
			closeFile();
		} else if(action == "remove_file") {
			removeFile();
		} else if(action == "refresh_project") {
			refreshProject();
		} else if(action == "save_file") {
			saveFile();
		} else if(action == "browse_examples") {
			browseExamples();
		} else if(action == "quit") {
			core->Shutdown();
		} else if(action == "run_project") {
			runProject();
		} else if(action == "export_project") {
			exportProject();
		} else if(action == "show_api") {
			openDocs();
		} else if(action == "show_about") {
			showAbout();
		} else if(action == "toggle_console") {
			toggleConsole();
		} else if(action == "settings") {
			showSettings();
		}
	}

	if(event->getDispatcher() == frame->console->backtraceWindow && event->getEventType() == "BackTraceEvent" && event->getEventCode() == BackTraceEvent::EVENT_BACKTRACE_SELECTED) {
		BackTraceEvent *btEvent = (BackTraceEvent*) event;
		openFileInProject(btEvent->project, btEvent->fileName);
		
		PolycodeEditor *editor = editorManager->getCurrentEditor();
		if(editor && editor->getEditorType() == "PolycodeTextEditor") {
			PolycodeTextEditor *textEditor = (PolycodeTextEditor*) editor;
			textEditor->highlightLine(btEvent->lineNumber);

		}
	}

	if(event->getDispatcher() == core) {
		switch(event->getEventCode()) {
			case Core::EVENT_LOST_FOCUS:
				core->setFramerate(3);
			break;
			case Core::EVENT_GAINED_FOCUS:
				core->setFramerate(30);
			break;
			case Core::EVENT_CORE_RESIZE:
				if(menuBar) {
					frame->Resize(core->getXRes(), core->getYRes()-25);
					menuBar->Resize(core->getXRes(), 25);
				} else {
					frame->Resize(core->getXRes(), core->getYRes());
				}
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
			PolycodeProjectBrowser *pb = frame->getProjectBrowser();
			BrowserUserData *selectedData = pb->getSelectedData();

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

			// don't open the editor if the selection was made by UITreeContainer arrow-key navigation
			if (selectedData && pb->treeContainer->getRootNode()->getSelectedNode()->isSelectedByKey() == false) {
				openFile(selectedData->fileEntry);
			}
		}
	}

	if(event->getDispatcher() == frame->playButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		willRunProject = true;
	}

	if(event->getDispatcher() == frame->stopButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		stopProject();
	}

	if(event->getDispatcher() == frame->yesNoCancelPopup) {
		if(frame->yesNoCancelPopup->action == "closeFile") {
			switch(event->getEventCode()) {
				case UIEvent::YES_EVENT:
				{
					PolycodeEditor *editor = editorManager->getCurrentEditor();
					if(editor) {
						editor->saveFile();
						closeFile();
					}
					frame->yesNoCancelPopup->action = "";
					frame->hideModal();
				}
				break;
				case UIEvent::NO_EVENT:
				{
					PolycodeEditor *editor = editorManager->getCurrentEditor();
					if(editor) {
						editor->setHasChanges(false);
						closeFile();
					}
					frame->yesNoCancelPopup->action = "";
					frame->hideModal();
				}
				break;
				case UIEvent::CANCEL_EVENT:
				break;
			}
		} else if(frame->yesNoCancelPopup->action == "closeQuitFile") {
			switch(event->getEventCode()) {
				case UIEvent::YES_EVENT:
				{
					PolycodeEditor *editor = editorManager->getCurrentEditor();
					if(editor) {
						editor->saveFile();
						closeFile();
					}
					frame->yesNoCancelPopup->action = "";
					frame->hideModal();
					if(quitApp()) {
						core->Shutdown();
					}
				}
				break;
				case UIEvent::NO_EVENT:
				{
					PolycodeEditor *editor = editorManager->getCurrentEditor();
					if(editor) {
						editor->setHasChanges(false);
						closeFile();
					}
					frame->yesNoCancelPopup->action = "";
					frame->hideModal();
					if(quitApp()) {
						core->Shutdown();
					}
				}
				break;
				case UIEvent::CANCEL_EVENT:
					quittingApp = false;
				break;
			}
		} else if (frame->yesNoCancelPopup->action == "closeProject") {
			switch (event->getEventCode()) {
				case UIEvent::YES_EVENT:
					saveFiles(tempEditorStore);
					doCloseProject();
					break;
				case UIEvent::NO_EVENT:
					doCloseProject();
					break;
				case UIEvent::CANCEL_EVENT:
					break;
			}
			frame->yesNoCancelPopup->action = "";
			frame->hideModal();
		}

		else if (frame->yesNoCancelPopup->action == "closeFiles") {
			switch (event->getEventCode()) {
				case UIEvent::YES_EVENT:
					saveFiles(tempEditorStore);
					doCloseFiles(tempEditorStore);
					break;
				case UIEvent::NO_EVENT:
					doCloseFiles(tempEditorStore);
					break;
				case UIEvent::CANCEL_EVENT:
					break;
			}
			frame->yesNoCancelPopup->action = "";
			frame->hideModal();
		}
	} else if(event->getDispatcher() == frame->yesNoPopup) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CANCEL_EVENT) {
			if(frame->yesNoPopup->action == "saveAndRun") {
				runNextFrame = true;
			}
			
			frame->hideModal();
			frame->yesNoPopup->action = "";
		}

		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			if(frame->yesNoPopup->action == "removeFile") {
				doRemoveFile();
			}

			if(frame->yesNoPopup->action == "saveAndRun") {
				editorManager->saveFilesForProject(projectManager->getActiveProject());
				runNextFrame = true;
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

	if(event->getDispatcher() == frame->settingsWindow && event->getEventType() == "UIEvent") {
		Config *config = CoreServices::getInstance()->getConfig();
		SettingsWindow *settingsWindow = frame->settingsWindow;

		if(event->getEventCode() == UIEvent::OK_EVENT) {
			config->setStringValue("Polycode", "useExternalTextEditor", settingsWindow->useExternalTextEditorBox->isChecked() ? "true" : "false");
			config->setStringValue("Polycode", "externalTextEditorCommand", settingsWindow->externalTextEditorCommand->getText());

			frame->hideModal();
		}
		if(event->getEventCode() == UIEvent::CLOSE_EVENT) {
			settingsWindow->updateUI();
		}
	}

	if(event->getDispatcher() == frame->exportProjectWindow && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		projectManager->exportProject(projectManager->getActiveProject(), frame->exportProjectWindow->projectLocationInput->getText(), frame->exportProjectWindow->macCheckBox->isChecked(), frame->exportProjectWindow->winCheckBox->isChecked(), frame->exportProjectWindow->linCheckBox->isChecked(), frame->exportProjectWindow->compileCheckBox->isChecked());
		frame->hideModal();
	}


	if(event->getDispatcher() == frame->newProjectWindow && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		projectManager->createNewProject(frame->newProjectWindow->getTemplateFolder(), frame->newProjectWindow->getProjectName(), frame->newProjectWindow->getProjectLocation());
		frame->hideModal();
	}

	if(event->getDispatcher() == frame->newFileWindow && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		projectManager->createNewFile(frame->newFileWindow->getTemplatePath(), frame->newFileWindow->getFileName());
		frame->hideModal();

		if(projectManager->getActiveProject()) {
			frame->projectBrowser->refreshProject(projectManager->getActiveProject());
		}
	}
	
	if(event->getDispatcher() == frame->exampleBrowserWindow) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
			String fullPath = String(core->getDefaultWorkingDirectory()+"/"+frame->exampleBrowserWindow->getExamplePath());
			PolycodeProject* project = projectManager->openProject(fullPath);
			OSFileEntry projectEntry = OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
			projectManager->setActiveProject(project);
			openFile(projectEntry);

			frame->hideModal();
		}
	}
	
	// close files and editors after the close file button is pressed
	if (event->getDispatcher() == frame->closeFileButton && event->getEventCode() == UIEvent::CLICK_EVENT) {
		if (core->getInput()->getKeyState(KEY_RSHIFT) || core->getInput()->getKeyState(KEY_LSHIFT))
			closeFiles(editorManager->openEditors);
		else
			closeFile();
	}
	
	// open an editor/file if project browser has focus and user hits enter or right-arrow key
	if (event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput() && event->getEventCode() == InputEvent::EVENT_KEYDOWN && frame->getProjectBrowser()->treeContainer->hasFocus) {
		InputEvent *inEvent = (InputEvent*)event;
		if (inEvent->keyCode() == KEY_RETURN || inEvent->keyCode() == KEY_RIGHT) {
			BrowserUserData *selectedData = frame->getProjectBrowser()->getSelectedData();
			if (selectedData)
				openFile(selectedData->fileEntry);
		}
	}
}

void PolycodeIDEApp::saveConfigFile() {
	Config *config = CoreServices::getInstance()->getConfig();
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

	configFile.root.addChild("settings");
	ObjectEntry *textEditorEntry = configFile.root["settings"]->addChild("text_editor");
	textEditorEntry->addChild("use_external", config->getStringValue("Polycode", "useExternalTextEditor"));
	textEditorEntry->addChild("command", config->getStringValue("Polycode", "externalTextEditorCommand"));

#if defined(__APPLE__) && defined(__MACH__)
	core->createFolder(core->getUserHomeDirectory()+"/Library/Application Support/Polycode");
	configFile.saveToXML(core->getUserHomeDirectory()+"/Library/Application Support/Polycode/config.xml");	
#else
	core->createFolder(core->getUserHomeDirectory()+"/.polycode");
	configFile.saveToXML(core->getUserHomeDirectory()+"/.polycode/config.xml");	

#endif
}

void PolycodeIDEApp::loadConfigFile() {
	Object configFile;
	// TODO: Make a crossplatform core method to get application data path
#if defined(__APPLE__) && defined(__MACH__)
	configFile.loadFromXML(core->getUserHomeDirectory()+"/Library/Application Support/Polycode/config.xml");
#else
	configFile.loadFromXML(core->getUserHomeDirectory()+"/.polycode/config.xml");
#endif
	globalSyntaxTheme = new SyntaxHighlightTheme();
	String themeName = "monokai";
	ObjectEntry *syntaxTheme = configFile.root["syntax_theme"];
	if(syntaxTheme) {
		themeName = syntaxTheme->stringVal;
	}
	globalSyntaxTheme->loadFromFile(themeName);

	if(configFile.root["open_projects"]) {
		ObjectEntry *projects = configFile.root["open_projects"];
		if(projects) {
			for(int i=0; i < projects->length; i++) {
				ObjectEntry *entry = (*(*projects)[i])["path"];
				if(entry) {
					PolycodeProject* project = projectManager->openProject(entry->stringVal);
					if(project) {
						OSFileEntry projectEntry = OSFileEntry(project->getProjectFile(), OSFileEntry::TYPE_FILE);
						projectManager->setActiveProject(project);
						openFile(projectEntry);
					}
				}
			}
		}
	}

	Config *config = CoreServices::getInstance()->getConfig();

	if(configFile.root["settings"]) {
		ObjectEntry *settings = configFile.root["settings"];
		ObjectEntry *textEditor = (*settings)["text_editor"];
		if(textEditor) {
			if((*textEditor)["use_external"]) {
				config->setStringValue("Polycode", "useExternalTextEditor", (*textEditor)["use_external"]->stringVal);
			} else {
				config->setStringValue("Polycode", "useExternalTextEditor", "false");
			}

			if((*textEditor)["command"]) {
				config->setStringValue("Polycode", "externalTextEditorCommand", (*textEditor)["command"]->stringVal);
			} else {
				config->setStringValue("Polycode", "externalTextEditorCommand", "");
			}
		}
	} else {
		config->setStringValue("Polycode","useExternalTextEditor", "false");
		config->setStringValue("Polycode", "externalTextEditorCommand", "");
	}
	frame->settingsWindow->updateUI();
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

	if(runNextFrame) {
		runNextFrame = false;
		doRunProject();
	}

	if(lastConnected != debugger->isConnected()) {
		needsRedraw = true;
		lastConnected = debugger->isConnected();
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


	return core->updateAndRender();
}

