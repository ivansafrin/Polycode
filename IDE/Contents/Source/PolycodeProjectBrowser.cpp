

#include "PolycodeProjectBrowser.h"

PolycodeProjectBrowser::PolycodeProjectBrowser() : ScreenEntity() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Projects", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	data->parentProject = NULL;
	treeContainer->getRootNode()->setUserData((void*) data)	;
	
	addChild(treeContainer);		
	treeContainer->setPosition(0,45);	
	
	selectedData = NULL;
}

PolycodeProjectBrowser::~PolycodeProjectBrowser() {
	
}

void PolycodeProjectBrowser::removeProject(PolycodeProject *project) {
	
	UITree *projectTree = treeContainer->getRootNode();
	
	for(int i=0; i < projectTree->getNumTreeChildren(); i++) {
		UITree *projectChild = projectTree->getTreeChild(i);
		BrowserUserData *userData = (BrowserUserData*)projectChild->getUserData();
		if(userData->parentProject == project) {
			projectTree->removeTreeChild(projectChild);
			return;
		}
	}
}

void PolycodeProjectBrowser::addProject(PolycodeProject *project) {
	UITree *projectTree = treeContainer->getRootNode()->addTreeChild("projectIcon.png", project->getProjectName(), (void*) project);
	projectTree->toggleCollapsed();
	
	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	data->parentProject = project;
	projectTree->setUserData((void*) data)	;
	
	parseFolderIntoNode(projectTree, project->getRootFolder(), project);	
}

void PolycodeProjectBrowser::handleEvent(Event *event) {
	
	if(event->getDispatcher() == treeContainer) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {			
			InputEvent *inputEvent = (InputEvent*) event;
			if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {				
				PolycodeProjectBrowserEvent *bEvent = new PolycodeProjectBrowserEvent();				
				dispatchEvent(bEvent, PolycodeProjectBrowserEvent::SHOW_MENU);
			}			
		}
	}
	
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			BrowserUserData *data = (BrowserUserData *)treeContainer->getRootNode()->getSelectedNode()->getUserData();
			selectedData =  data;
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	
	ScreenEntity::handleEvent(event);
}

void PolycodeProjectBrowser::parseFolderIntoNode(UITree *node, String spath, PolycodeProject *parentProject) {
	printf("Parsing %s\n", spath.c_str());
	vector<OSFileEntry> files = OSBasics::parseFolder(spath, false);
	for(int i=0; i < files.size(); i++) {
		OSFileEntry entry = files[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			UITree *newChild = node->addTreeChild("folder.png", entry.name, (void*) data);
			data->type = 2;	
			data->parentProject = parentProject;
			parseFolderIntoNode(newChild, entry.fullPath, parentProject);
		} else {
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			data->type = 1;
			data->parentProject = parentProject;			
			UITree *newChild = node->addTreeChild("file.png", entry.name, (void*) data);			
		}
	}	
}

void PolycodeProjectBrowser::Resize(int newWidth, int newHeight) {
	treeContainer->Resize(newWidth, newHeight);
}
