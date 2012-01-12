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
