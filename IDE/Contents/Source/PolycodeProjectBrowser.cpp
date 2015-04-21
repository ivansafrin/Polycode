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

PolycodeProjectBrowser::PolycodeProjectBrowser(PolycodeProject *project) : UIElement() {

	this->project = project;	
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel("PROJECT BROWSER", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	
	addChild(label);
	label->setPosition(10, 3);


	treeContainer = new UITreeContainer("boxIcon.png", project->getProjectName(), 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	treeContainer->setPosition(0, 30);
	
	BrowserUserData *data = new BrowserUserData();
	data->type = 0;
	data->parentProject = project;
	treeContainer->getRootNode()->setUserData((void*) data)	;

	addChild(treeContainer);		
	selectedData = NULL;
	
	parseFolderIntoNode(treeContainer->getRootNode(), project->getRootFolder());
}

PolycodeProjectBrowser::~PolycodeProjectBrowser() {
	
}

void PolycodeProjectBrowser::Refresh() {
	parseFolderIntoNode(treeContainer->getRootNode(), project->getRootFolder());		
}

void PolycodeProjectBrowser::handleEvent(Event *event) {

	if(event->getDispatcher() == contextMenu) {
		UIMenuItem *item = contextMenu->getSelectedItem();

		PolycodeProjectBrowserEvent *bEvent = new PolycodeProjectBrowserEvent();
		bEvent->command = item->_id;
		dispatchEvent(bEvent, PolycodeProjectBrowserEvent::HANDLE_MENU_COMMAND);
						
	}
	
	if(event->getDispatcher() == treeContainer) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {			
			InputEvent *inputEvent = (InputEvent*) event;
			if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {				

			contextMenu = globalMenu->showMenuAtMouse(130);


			contextMenu->addOption("New File", "add_new_file");
			contextMenu->addOption("New Project", "add_new_project");
			contextMenu->addOption("New Folder", "add_new_folder");
			contextMenu->addDivider();
			contextMenu->addOption("Add external files", "add_files");
			contextMenu->addOption("Import 3D assets", "import_assets");
			contextMenu->addDivider();
			contextMenu->addOption("Refresh", "refresh");
			if (treeContainer->getRootNode() == treeContainer->getRootNode()->getSelectedNode()){
				contextMenu->addOption("Close Project", "close_project");
			} else {
				contextMenu->addOption("Rename", "rename");
				contextMenu->addDivider();
				contextMenu->addOption("Remove", "remove");
			}

			contextMenu->fitToScreenVertical();
			
			contextMenu->addEventListener(this, UIEvent::OK_EVENT);
											
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
	
	Entity::handleEvent(event);
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

void parseOpenNodesIntoEntry(ObjectEntry *entry, UITree *node, bool addNewNode) {

	bool hasOpenNodes = false;
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);	
		if(!child->isCollapsed()) {	
			hasOpenNodes = true;
		}
	}

	if(!hasOpenNodes) {
		return;		
	}

	ObjectEntry *childNodes = entry;
	if(addNewNode) {
		childNodes = entry->addChild("child_nodes");
	}
	
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);
		if(!child->isCollapsed()) {
			ObjectEntry *newEntry = childNodes->addChild("open_node");
			newEntry->addChild("name", child->getLabelText());			
			parseOpenNodesIntoEntry(newEntry, child, true);
		}
	}
}

ObjectEntry *PolycodeProjectBrowser::getBrowserConfig() {
	ObjectEntry *configEntry = new ObjectEntry();	
	configEntry->name = "project_browser";
	
	configEntry->addChild("width", getWidth());	
	ObjectEntry *openNodes = configEntry->addChild("open_nodes");
	parseOpenNodesIntoEntry(openNodes, treeContainer->getRootNode(), false);
	
	return configEntry;
}

void PolycodeProjectBrowser::applyOpenNodeToTree(UITree* treeNode, ObjectEntry *nodeEntry) {
	for(int i=0; i < treeNode->getNumTreeChildren(); i++) {
		if(treeNode->getTreeChild(i)->getLabelText() == (*nodeEntry)["name"]->stringVal ){
			if(treeNode->getTreeChild(i)->isCollapsed()) {
				treeNode->getTreeChild(i)->toggleCollapsed();
				ObjectEntry *childNodes = (*nodeEntry)["child_nodes"];
				if(childNodes) {
					for(int j=0; j < childNodes->length; j++) {
						applyOpenNodeToTree(treeNode->getTreeChild(i), (*childNodes)[j]);
					}
				}
			}
		}
	}
}

void PolycodeProjectBrowser::applyBrowserConfig(ObjectEntry *entry) {
	ObjectEntry *openNodes = (*entry)["open_nodes"];
	if(openNodes) {
		for(int i=0; i < openNodes->length; i++) {
			ObjectEntry *openNode = (*openNodes)[i];
			if(openNode) {				
				applyOpenNodeToTree(treeContainer->getRootNode(), openNode);
			}
		}
	}
}

String PolycodeProjectBrowser::getIconForExtension(String extension) {
    if(extension == "mesh") {
        return "treeIcons/mesh.png";
    } else if(extension == "png" || extension == "hdr" || extension == "jpg" || extension == "tga" || extension == "psd") {
        return "treeIcons/image.png";
    } else if(extension == "frag" || extension == "vert") {
        return "treeIcons/shader.png";
    } else if(extension == "otf" || extension == "ttf") {
        return "treeIcons/font.png";
    } else if(extension == "skeleton") {
        return "treeIcons/skeleton.png";
    } else if(extension == "anim") {
        return "treeIcons/animation.png";
    } else if(extension == "ogg" || extension == "wav") {
        return "treeIcons/sound.png";
    } else if(extension == "entity") {
        return "treeIcons/entity.png";
    } else if(extension == "mat") {
        return "treeIcons/materials.png";
    } else if(extension == "sprite" || extension == "sprites") {
        return "treeIcons/sprites.png";
    } else if(extension == "polyproject") {
        return "treeIcons/project.png";
    } else {
        return "file.png";
    }
}

void PolycodeProjectBrowser::parseFolderIntoNode(UITree *node, String spath) {
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
				data->parentProject = project;
				parseFolderIntoNode(newChild, entry.fullPath);				
			} else {
				parseFolderIntoNode(existing, entry.fullPath);							
			}
		} else {
			if(!nodeHasName(node, entry.name)) {
				BrowserUserData *data = new BrowserUserData();
				data->fileEntry = entry;
				data->type = 1;
				data->parentProject = project;			
				node->addTreeChild(getIconForExtension(entry.extension), entry.name, (void*) data);
			}
		}
	}		
	
}

void PolycodeProjectBrowser::Resize(Number width, Number height) {
	headerBg->Resize(width, 30);
	treeContainer->Resize(width, height-30);
	UIElement::Resize(width, height);
}
