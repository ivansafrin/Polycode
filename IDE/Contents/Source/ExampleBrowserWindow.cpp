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

#include "ExampleBrowserWindow.h"

ExampleBrowserWindow::ExampleBrowserWindow() : UIWindow(L"Example Browser", 320, 300){
	
	templateFolder = "";
	
	closeOnEscape = true;
	defaultTemplateTree = NULL;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");
	
	
	templateContainer = new UITreeContainer("boxIcon.png", L"Examples", 300, 300-topPadding-padding-padding- 40);	
	
	ExampleTemplateUserData *data = new ExampleTemplateUserData();
	data->type = 0;
	templateContainer->getRootNode()->setUserData(data);			
	
	
	addChild(templateContainer);		
	templateContainer->setPosition(padding,topPadding+padding);	
	templateContainer->getRootNode()->toggleCollapsed();
	
	templateContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	
	vector<OSFileEntry> templates = OSBasics::parseFolder(RESOURCE_PATH"Standalone/Examples/Lua", false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = templateContainer->getRootNode()->addTreeChild("folder.png", entry.name, NULL);			
			ExampleTemplateUserData *data = new ExampleTemplateUserData();
			data->type = 0;
			newChild->setUserData(data);			
			if(i == 0) {
				newChild->toggleCollapsed();
			}
			parseTemplatesIntoTree(newChild, entry);
		}
	}
	
	
	
	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(300-100-padding-80-10, 265);
		
	
	okButton = new UIButton(L"Open Example", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(300-80-padding, 265);
}

String ExampleBrowserWindow::getExamplePath() {
	String suffix;
	std::vector<String> parts = templateFolder.split("/");	
	return templateFolder+"/"+parts[parts.size()-1]+".xml";
}


void ExampleBrowserWindow::ResetForm() {
	if(defaultTemplateTree)
		defaultTemplateTree->setSelected();
}

void ExampleBrowserWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);						
			}
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);				
			}									
		}
	}
	
	if(event->getEventType() == "UITreeEvent" && event->getEventCode() == UITreeEvent::SELECTED_EVENT) {
		if(event->getDispatcher() == templateContainer->getRootNode()) {
			UITreeEvent *treeEvent = (UITreeEvent*) event;
			ExampleTemplateUserData *data = (ExampleTemplateUserData *)treeEvent->selection->getUserData();
			if(data->type == 1)
				templateFolder = data->templateFolder;
		}
	}
	
	UIWindow::handleEvent(event);	
}

void ExampleBrowserWindow::parseTemplatesIntoTree(UITree *tree, OSFileEntry folder) {
	vector<OSFileEntry> templates = OSBasics::parseFolder(folder.fullPath, false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = tree->addTreeChild("templateIcon.png", entry.name, NULL);			
			ExampleTemplateUserData *data = new ExampleTemplateUserData();
			data->type = 1;
			data->templateFolder = entry.fullPath;
			newChild->setUserData(data);
			if(entry.name == "Empty Project") {
				defaultTemplateTree = newChild;
				newChild->setSelected();
			}
		}
	}	
}



ExampleBrowserWindow::~ExampleBrowserWindow() {
	
}

