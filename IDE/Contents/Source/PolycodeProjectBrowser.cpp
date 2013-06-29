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

#include "PolycodeProjectBrowser.h"

extern UIGlobalMenu *globalMenu;

PolycodeProjectBrowser::PolycodeProjectBrowser() : UIElement() {

	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	ScreenLabel *label = new ScreenLabel("PROJECT BROWSER", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));

	addChild(label);
	label->setPosition(10, 3);


	treeContainer = new UITreeContainer("boxIcon.png", L"Projects", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	treeContainer->setPosition(0, 30);

	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	data->parentProject = NULL;
	treeContainer->getRootNode()->setUserData((void*) data)	;

	addChild(treeContainer);
	selectedData = NULL;
}

PolycodeProjectBrowser::~PolycodeProjectBrowser() {

}

void PolycodeProjectBrowser::refreshProject(PolycodeProject *project) {

	UITree *projectTree = treeContainer->getRootNode();

	for(int i=0; i < projectTree->getNumTreeChildren(); i++) {
		UITree *projectChild = projectTree->getTreeChild(i);
		BrowserUserData *userData = (BrowserUserData*)projectChild->getUserData();
		if(userData->parentProject == project) {
			parseFolderIntoNode(projectChild, project->getRootFolder(), project);
			return;
		}
	}

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
	data->type = 3;
	data->parentProject = project;
	projectTree->setUserData((void*) data)	;

	parseFolderIntoNode(projectTree, project->getRootFolder(), project);
}

void PolycodeProjectBrowser::handleEvent(Event *event) {

	if(event->getDispatcher() == contextMenu) {
		UIMenuItem *item = contextMenu->getSelectedItem();

		PolycodeProjectBrowserEvent *bEvent = new PolycodeProjectBrowserEvent();
		bEvent->command = item->_id;
		dispatchEvent(bEvent, PolycodeProjectBrowserEvent::HANDLE_MENU_COMMAND);

	}

	if(event->getDispatcher() == treeContainer && event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
		InputEvent *inputEvent = (InputEvent*) event;
		if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {

			contextMenu = globalMenu->showMenuAtMouse(130);


			contextMenu->addOption("New File", "add_new_file");
			contextMenu->addOption("New Project", "add_new_project");
			contextMenu->addOption("New Folder", "add_new_folder");
			contextMenu->addOption("----------------", "");
			contextMenu->addOption("Add external files", "add_files");
			contextMenu->addOption("----------------", "");
			contextMenu->addOption("Refresh", "refresh");
			contextMenu->addOption("Rename", "rename");
			contextMenu->addOption("----------------", "");
			contextMenu->addOption("Remove", "remove");

			contextMenu->fitToScreenVertical();

			contextMenu->addEventListener(this, UIEvent::OK_EVENT);

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

UITree *PolycodeProjectBrowser::nodeHasName(UITree *node, String name) {
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *projectChild = node->getTreeChild(i);
		if(projectChild->getLabelText() == name) {
			return projectChild;
		}
	}
	return NULL;
}

bool PolycodeProjectBrowser::listHasFileEntry(vector<OSFileEntry> files, OSFileEntry fileEntry) {
	for(int i=0; i < files.size(); i++) {
		if(files[i].fullPath == fileEntry.fullPath && files[i].type == fileEntry.type) {
			return true;
		}
	}
	return false;
}

void PolycodeProjectBrowser::parseFolderIntoNode(UITree *node, String spath, PolycodeProject *parentProject) {
	vector<OSFileEntry> files = OSBasics::parseFolder(spath, false);

	// check if files got deleted
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *projectChild = node->getTreeChild(i);
		if(!listHasFileEntry(files, ((BrowserUserData*)projectChild->getUserData())->fileEntry)) {
			node->removeTreeChild(projectChild);
		}
	}

	for(int i=0; i < files.size(); i++) {
		OSFileEntry entry = files[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *existing = nodeHasName(node, entry.name);
			if(!existing) {
				BrowserUserData *data = new BrowserUserData();
				data->fileEntry = entry;
				UITree *newChild = node->addTreeChild("folder.png", entry.name, (void*) data);
				data->type = 2;	
				data->parentProject = parentProject;
				parseFolderIntoNode(newChild, entry.fullPath, parentProject);
			} else {
				parseFolderIntoNode(existing, entry.fullPath, parentProject);
			}
		} else if(!nodeHasName(node, entry.name)) {
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			data->type = 1;
			data->parentProject = parentProject;
			UITree *newChild = node->addTreeChild("file.png", entry.name, (void*) data);
		}
	}

}

void PolycodeProjectBrowser::Resize(Number width, Number height) {
	headerBg->setShapeSize(width, 30);
	treeContainer->Resize(width, height-30);
}
