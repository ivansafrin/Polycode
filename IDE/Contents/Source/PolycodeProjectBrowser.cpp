

#include "PolycodeProjectBrowser.h"

PolycodeProjectBrowser::PolycodeProjectBrowser() : ScreenEntity() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Projects", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	
	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	treeContainer->getRootNode()->setUserData((void*) data)	;
	
	addChild(treeContainer);		
	treeContainer->setPosition(0,45);	
	
	selectedData = NULL;
}

PolycodeProjectBrowser::~PolycodeProjectBrowser() {
	
}

void PolycodeProjectBrowser::addProject(PolycodeProject *project) {
	UITree *projectTree = treeContainer->getRootNode()->addTreeChild("projectIcon.png", project->getProjectName(), (void*) project);
	projectTree->toggleCollapsed();
	
	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	projectTree->setUserData((void*) data)	;
	
	parseFolderIntoNode(projectTree, project->getRootFolder());	
}

void PolycodeProjectBrowser::handleEvent(Event *event) {
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			BrowserUserData *data = (BrowserUserData *)treeContainer->getRootNode()->getSelectedNode()->getUserData();
			if(data->type != 0) {
				selectedData =  data;
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			}
		}
	}
	
	ScreenEntity::handleEvent(event);
}

void PolycodeProjectBrowser::parseFolderIntoNode(UITree *node, String spath) {
	printf("Parsing %s\n", spath.c_str());
	vector<OSFileEntry> files = OSBasics::parseFolder(spath, false);
	for(int i=0; i < files.size(); i++) {
		OSFileEntry entry = files[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			UITree *newChild = node->addTreeChild("folder.png", entry.name, (void*) data);
			data->type = 2;			
			parseFolderIntoNode(newChild, entry.fullPath);
		} else {
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			data->type = 1;
			UITree *newChild = node->addTreeChild("file.png", entry.name, (void*) data);			
		}
	}	
}

void PolycodeProjectBrowser::Resize(int newWidth, int newHeight) {
	treeContainer->Resize(newWidth, newHeight);
}
