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

#include "NewProjectWindow.h"
#include "PolycodeFrame.h"

extern PolycodeFrame *globalFrame;

NewProjectWindow::NewProjectWindow() : UIWindow(L"Create New Project", 480, 280){

	templateFolder = "";

	closeOnEscape = true;
	defaultTemplateTree = NULL;

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");


	templateContainer = new UITreeContainer("boxIcon.png", L"Templates", 200, 300-topPadding-padding-padding);	

	TemplateUserData *data = new TemplateUserData();
	data->type = 0;
	templateContainer->getRootNode()->setUserData(data);


	addChild(templateContainer);
	templateContainer->setPosition(padding,topPadding+padding);
	templateContainer->getRootNode()->toggleCollapsed();

	templateContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);

	vector<OSFileEntry> templates = OSBasics::parseFolder(RESOURCE_PATH"ProjectTemplates", false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = templateContainer->getRootNode()->addTreeChild("folder.png", entry.name, NULL);
			TemplateUserData *data = new TemplateUserData();
			data->type = 0;
			newChild->setUserData(data);
			if(i == 0) {
				newChild->toggleCollapsed();
			}
			parseTemplatesIntoTree(newChild, entry);
		}
	}

	ScreenLabel *label2 = new ScreenLabel(L"PROJECT NAME", 18, "section", Label::ANTIALIAS_FULL);
	label2->color.a = 0.4;
	addChild(label2);
	label2->setPosition(padding+220, templateContainer->getPosition().y-2);

	projectNameInput = new UITextInput(false, 500-padding-210-padding-padding, 12);	
	addChild(projectNameInput);
	projectNameInput->setPosition(label2->getPosition().x-6, label2->getPosition().y + 25);

	ScreenLabel *label3 = new ScreenLabel(L"PROJECT LOCATION", 18, "section", Label::ANTIALIAS_FULL);
	label3->color.a = 0.4;
	addChild(label3);
	label3->setPosition(padding+220, templateContainer->getPosition().y+65);

	projectLocationInput = new UITextInput(false, 500-padding-210-padding-padding, 12);
	addChild(projectLocationInput);
	projectLocationInput->setPosition(label3->getPosition().x-6, label3->getPosition().y+25);


	locationSelectButton = new UIButton(L"Choose...", 100);
	locationSelectButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(locationSelectButton);
	locationSelectButton->setPosition(500-103-padding, projectLocationInput->getPosition().y+projectLocationInput->getHeight()+10);


	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(500-100-padding-100-10, 265);


	okButton = new UIButton(L"Create Project", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(500-100-padding, 265);
}

String NewProjectWindow::getTemplateFolder() {
	return templateFolder;
}

String NewProjectWindow::getProjectName() {
	return projectNameInput->getText();
}

String NewProjectWindow::getProjectLocation() {
	return projectLocationInput->getText();
}


void NewProjectWindow::ResetForm() {
	if(defaultTemplateTree)
		defaultTemplateTree->setSelected();
	focusChild(projectNameInput);	
	projectNameInput->setText(L"Untitled");
	projectLocationInput->setText(CoreServices::getInstance()->getCore()->getUserHomeDirectory()+"/Documents/Polycode");
}

void NewProjectWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::OK_EVENT && event->getDispatcher() == globalFrame->fileDialog) {
			String pathName = globalFrame->fileDialog->getSelection();
			if(pathName != "")
				projectLocationInput->setText(pathName);

		}

		if(enabled && event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
			}
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
			}

			if(event->getDispatcher() == locationSelectButton) {
#ifdef USE_POLYCODEUI_FILE_DIALOGS
				std::vector<String> exts;
				globalFrame->showFileBrowser(CoreServices::getInstance()->getCore()->getUserHomeDirectory(),  true, exts, false);
				globalFrame->fileDialog->addEventListener(this, UIEvent::OK_EVENT);
#else
				String pathName = CoreServices::getInstance()->getCore()->openFolderPicker();
				if(pathName != "")
					projectLocationInput->setText(pathName);
#endif
			}

		}
	}

	if(event->getEventType() == "UITreeEvent" && event->getEventCode() == UITreeEvent::SELECTED_EVENT) {
		if(event->getDispatcher() == templateContainer->getRootNode()) {
			UITreeEvent *treeEvent = (UITreeEvent*) event;
			TemplateUserData *data = (TemplateUserData *)treeEvent->selection->getUserData();
			if(data->type == 1)
				templateFolder = data->templateFolder;
		}
	}

	UIWindow::handleEvent(event);
}

void NewProjectWindow::parseTemplatesIntoTree(UITree *tree, OSFileEntry folder) {
	vector<OSFileEntry> templates = OSBasics::parseFolder(folder.fullPath, false);
	for(int i=0; i < templates.size(); i++) {
		OSFileEntry entry = templates[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UITree *newChild = tree->addTreeChild("templateIcon.png", entry.name, NULL);
			TemplateUserData *data = new TemplateUserData();
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



NewProjectWindow::~NewProjectWindow() {

}

