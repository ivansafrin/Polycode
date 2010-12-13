
#include "NewFileWindow.h"

NewFileWindow::NewFileWindow() : UIWindow(L"Create New File", 500, 300) {
	defaultTemplateTree = NULL;
	
	templateContainer = new UITreeContainer("boxIcon.png", L"File Templates", 200, 300-topPadding-padding-padding);	
	
	FileTemplateUserData *data = new FileTemplateUserData();
	data->type = 0;
	templateContainer->getRootNode()->setUserData(data);			

	addChild(templateContainer);		
	templateContainer->setPosition(padding,topPadding+padding);	
	templateContainer->getRootNode()->toggleCollapsed();
	
	templateContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	
	
	vector<OSFileEntry> templates = OSBasics::parseFolder(RESOURCE_PATH"FileTemplates", false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = templateContainer->getRootNode()->addTreeChild("folder.png", entry.name, NULL);			
			FileTemplateUserData *data = new FileTemplateUserData();
			data->type = 0;
			newChild->setUserData(data);			
			newChild->toggleCollapsed();
			parseTemplatesIntoTree(newChild, entry);
		}
	}	
}

NewFileWindow::~NewFileWindow() {
	
}

void NewFileWindow::resetForm() {
	defaultTemplateTree->setSelected();
}

void NewFileWindow::parseTemplatesIntoTree(UITree *tree, OSFileEntry folder) {
	vector<OSFileEntry> templates = OSBasics::parseFolder(folder.fullPath, false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type != OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = tree->addTreeChild("templateIcon.png", entry.nameWithoutExtension, NULL);			
			FileTemplateUserData *data = new FileTemplateUserData();
			data->type = 1;
			data->templateFolder = entry.fullPath;
			newChild->setUserData(data);
			if(entry.name == "LUA Source File.lua") {
				defaultTemplateTree = newChild;
				newChild->setSelected();
			}
		}
	}	
}
