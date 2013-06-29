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

NewFileWindow::NewFileWindow() : UIWindow(L"Create New File", 580, 280) {
	defaultTemplateTree = NULL;

	Config *conf = CoreServices::getInstance()->getConfig();
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");
	
	closeOnEscape = true;

	templateContainer = new UITreeContainer("boxIcon.png", L"File Templates", 250, 300-topPadding-padding-padding);	

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

	ScreenLabel *label2 = new ScreenLabel(L"NEW FILE NAME (NO EXTENSION)", 18, "section", Label::ANTIALIAS_FULL);
	label2->color.a = 0.4;
	label2->getLabel()->setColorForRange(Color(),0, 12);
	label2->getLabel()->setColorForRange(Color(0.6, 0.6, 0.6, 1.0),12, 40);
	label2->setText("NEW FILE NAME (NO EXTENSION)");

	addChild(label2);
	label2->setPosition(padding+270, templateContainer->getPosition().y-5);

	fileNameInput = new UITextInput(false, 550-padding-210-padding-padding, 12);
	addChild(fileNameInput);
	fileNameInput->setPosition(label2->getPosition().x, label2->getPosition().y+30);


	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(600-100-padding-100-10, 265);

	okButton = new UIButton(L"Create File", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(600-100-padding, 265);
}

NewFileWindow::~NewFileWindow() {

}

String NewFileWindow::getFileName() {
	return fileNameInput->getText();
}

String NewFileWindow::getTemplatePath() {
	return templatePath;
}

void NewFileWindow::resetForm() {
	defaultTemplateTree->setSelected();
	fileNameInput->setText("Untitled");
}

void NewFileWindow::handleEvent(Event *event) {

	if(enabled && event->getEventType() == "UIEvent") {
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
			FileTemplateUserData *data = (FileTemplateUserData *)treeEvent->selection->getUserData();
			if(data->type == 1)
				templatePath = data->templatePath;
		}
	}

	UIWindow::handleEvent(event);
}


void NewFileWindow::parseTemplatesIntoTree(UITree *tree, OSFileEntry folder) {
	vector<OSFileEntry> templates = OSBasics::parseFolder(folder.fullPath, false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type != OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = tree->addTreeChild("templateIcon.png", entry.nameWithoutExtension, NULL);
			FileTemplateUserData *data = new FileTemplateUserData();
			data->type = 1;
			data->templatePath = entry.fullPath;
			newChild->setUserData(data);
			if(entry.name == "Lua Script.lua") {
				defaultTemplateTree = newChild;
				newChild->setSelected();
			}
		}
	}
}
