

#include "NewProjectWindow.h"


NewProjectWindow::NewProjectWindow() : UIWindow(L"Create New Project", 500, 300){
	
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
	
	ScreenLabel *label2 = new ScreenLabel(fontName, L"Project Name", fontSize, Label::ANTIALIAS_FULL);
	addChild(label2);
	label2->setPosition(padding+220, templateContainer->getPosition()->y);		

	projectNameInput = new UITextInput(false, 500-padding-220-padding-padding, 12);	
	addChild(projectNameInput);
	projectNameInput->setPosition(label2->getPosition()->x, label2->getPosition()->y+label2->getHeight()+2);
	
	ScreenLabel *label3 = new ScreenLabel(fontName, L"Project Location", fontSize, Label::ANTIALIAS_FULL);
	addChild(label3);
	label3->setPosition(padding+220, templateContainer->getPosition()->y+50);		
	
	projectLocationInput = new UITextInput(false, 500-padding-220-padding-padding, 12);	
	addChild(projectLocationInput);
	projectLocationInput->setPosition(label3->getPosition()->x, label3->getPosition()->y+label3->getHeight()+2);

	
	locationSelectButton = new UIButton(L"Choose...", 100);
	locationSelectButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	addChild(locationSelectButton);
	locationSelectButton->setPosition(500-100-padding, projectLocationInput->getPosition()->y+projectLocationInput->getHeight()+5);
	
	
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
	projectLocationInput->setText(L"~/Documents/Polycode");
}

void NewProjectWindow::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);						
			}
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);				
			}			
			
			if(event->getDispatcher() == locationSelectButton) {
				String pathName = CoreServices::getInstance()->getCore()->openFolderPicker();
				projectLocationInput->setText(pathName);
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

