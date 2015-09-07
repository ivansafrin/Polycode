
#include "PolyUIFileDialog.h"
#include "PolyConfig.h"
#include "PolyRenderer.h"

using namespace Polycode;

UIFileDialogEntry::UIFileDialogEntry(OSFileEntry entry, bool canSelect, int width, bool isPlace) : UIElement() {
	this->canSelect = canSelect;
	ownsChildren = true;

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fileIconName = conf->getStringValue("Polycode", "uiFileBrowserFileIcon");
	String folderIconName = conf->getStringValue("Polycode", "uiFileBrowserFolderIcon");
	String placeIconName = conf->getStringValue("Polycode", "uiFileBrowserPlaceIcon");

	bg = new UIRect(width, 18);
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(bg);
	bg->setColor(0.5, 0.5, 0.5, 1.0);
	bg->processInputEvents = true;
	bg->visible = false;

	this->fileEntry = entry;

	if(isPlace) {
		icon = new UIImage(placeIconName);
	} else {
		if(entry.type == OSFileEntry::TYPE_FILE) {
			icon = new UIImage(fileIconName);
		} else {
			icon = new UIImage(folderIconName);
		}
	}

	icon->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	addChild(icon);
	icon->setPosition(3,1);

	label = new UILabel(entry.name, 12, "sans");
	addChild(label);
	label->setPosition(25, 2);

	if(!canSelect) {
		label->color.a = 0.3;
	}

}

void UIFileDialogEntry::Select() {
	bg->visible = true;
}

void UIFileDialogEntry::Deselect() {
	bg->visible = false;
}

UIFileDialogEntry::~UIFileDialogEntry() {

}

UIFileDialog::UIFileDialog(String baseDir, bool foldersOnly, std::vector<String> extensions, bool allowMultiple) : UIWindow("", 500, 400) {
	this->foldersOnly = foldersOnly;
	this->allowMultiple = allowMultiple;

	this->extensions = extensions;

	closeOnEscape = true;

	if(foldersOnly) {
		setWindowCaption("Select a folder");
	} else {
		if(allowMultiple) {
			setWindowCaption("Select files");
		} else {
			setWindowCaption("Select a file");
		}
	}

	cancelButton = new UIButton("Cancel", 100);
	addChild(cancelButton);
	cancelButton->setPosition(500-210, 400 - 20);

	okButton = new UIButton("OK",  100);
	addChild(okButton);
	okButton->setPosition(500-100, 400 - 20);

	newFolderButton = new UIButton("New Folder", 100);
	addChild(newFolderButton);
	newFolderButton->setPosition(25, 400-20);

	newFolderButton->addEventListener(this, UIEvent::CLICK_EVENT);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);

	entryHolder = new UIElement();
	entryHolder->ownsChildren = true;
	entryHolder->setWidth(1);
	entryHolder->setHeight(1);
	
	scrollContainer = new UIScrollContainer(entryHolder, false, true, 500-140, 320);
	addChild(scrollContainer);

	scrollContainer->setPosition(160, 40);
	showFolder(baseDir);

	createFolderWindow = new CreateFolderWindow();
	createFolderWindow->visible = false;
	createFolderWindow->enabled = false;

	createFolderWindow->setPosition(100, 150);

	createFolderWindow->okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	createFolderWindow->cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);

	addChild(createFolderWindow);

	doChangeFolder = false;
	addToSidebar("/", "Filesystem");
	addToSidebar(CoreServices::getInstance()->getCore()->getUserHomeDirectory(), "Home");
}

bool UIFileDialog::canOpen(String extension) {
	if(extensions.empty()) {
		return true;
	}
	
	for(int i=0; i < extensions.size(); i++) {
		if(extensions[i] == extension) {
			return true;
		}
	}
	return false;
}

void UIFileDialog::addToSidebar(String path, String name) {
	OSFileEntry backEntry;
	backEntry.type = OSFileEntry::TYPE_FOLDER;
	backEntry.name = name;
	backEntry.fullPath = path;

	UIFileDialogEntry *newEntry = new UIFileDialogEntry(backEntry, true, 140, true);
	addChild(newEntry);
	newEntry->setPosition(10, 40 + (sideBarEntries.size() * 20));
	sideBarEntries.push_back(newEntry);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
}

void UIFileDialog::clearEntries() {
	for(int i=0; i < entries.size(); i++) {
		entryHolder->removeChild(entries[i]);
		delete entries[i];	
	}
	entries.clear();
}

void UIFileDialog::onClose() {
	dispatchEvent(new UIEvent(), UIEvent::CANCEL_EVENT);
}

String UIFileDialog::getSelection() {
	return selection;
}

void UIFileDialog::showFolder(String folderPath) {
	doChangeFolder = false;

	currentFolderPath = folderPath;

	if(foldersOnly) {
		selection = folderPath;
	} else {
		selection = "";
	}


	for(int i=0; i < sideBarEntries.size(); i++) {
		sideBarEntries[i]->Deselect();
	}

	currentEntry = NULL;
	clearEntries();

	std::vector<OSFileEntry> _entries = OSBasics::parseFolder(folderPath, false);
	
	int offset = 0;
	if(folderPath != "/") {
	offset = 1;
	OSFileEntry backEntry;
	backEntry.type = OSFileEntry::TYPE_FOLDER;
	backEntry.name = "..";
	backEntry.basePath = folderPath;
	backEntry.fullPath = folderPath+"/..";

	UIFileDialogEntry *newEntry = new UIFileDialogEntry(backEntry, true);
	entryHolder->addChild(newEntry);
	entries.push_back(newEntry);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);
	newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	}

	int i;
	for(i=0; i < _entries.size(); i++) {
		bool canSelect = false;

		if(_entries[i].type == OSFileEntry::TYPE_FOLDER) {
			canSelect = true;
		}

		if(foldersOnly) {
		} else {
			if(canOpen(_entries[i].extension)) {
				canSelect = true;
			}
		}
		UIFileDialogEntry *newEntry = new UIFileDialogEntry(_entries[i], canSelect);
		entryHolder->addChild(newEntry);
		newEntry->setPosition(0, (i+offset) * 20);
		entries.push_back(newEntry);	
		newEntry->bg->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);
		newEntry->bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	}
	scrollContainer->setContentSize(500-160, (i+offset) * 20);
}

void UIFileDialog::Update() {
	if(doChangeFolder) {
		showFolder(newPath);
		doChangeFolder = false;
	}
}

void UIFileDialog::handleEvent(Event *event) {

	for(int i=0; i < sideBarEntries.size(); i++) {
		if(event->getDispatcher() == sideBarEntries[i]->bg) {
			showFolder(sideBarEntries[i]->fileEntry.fullPath);
			sideBarEntries[i]->Select();
		}
	}

	for(int i=0; i < entries.size(); i++) {
		if(event->getDispatcher() == entries[i]->bg) {
			
			switch(event->getEventCode()) {
				case InputEvent::EVENT_DOUBLECLICK:
					if(entries[i]->fileEntry.type == OSFileEntry::TYPE_FOLDER && entries[i]->canSelect) {
						doChangeFolder = true;
						if(entries[i]->fileEntry.name == "..") {
							std::vector<String> bits = currentFolderPath.split("/");
							newPath = "";
							if(bits.size() > 2) {
								for(int i=1; i < bits.size()-1; i++) {
									newPath += "/"+bits[i];
								}
							} else {
								newPath = "/";
							}
						} else{
							newPath = entries[i]->fileEntry.fullPath;
						}
					}
				break;
				case InputEvent::EVENT_MOUSEDOWN:
					if(entries[i]->canSelect) {
						if(currentEntry)
							currentEntry->Deselect();
						entries[i]->Select();
						currentEntry = entries[i];

						if((foldersOnly &&  entries[i]->fileEntry.type == OSFileEntry::TYPE_FOLDER) 
							|| (!foldersOnly &&  entries[i]->fileEntry.type == OSFileEntry::TYPE_FILE)) {
							selection = entries[i]->fileEntry.fullPath;
						}
					}
				break;
			}
		}
	}

	if(event->getDispatcher() == okButton) {
		dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);
	}

	if(event->getDispatcher() == cancelButton) {
		dispatchEvent(new UIEvent(), UIEvent::CANCEL_EVENT);
	}

	if(event->getDispatcher() == createFolderWindow->okButton) {
		CoreServices::getInstance()->getCore()->createFolder(currentFolderPath+"/"+createFolderWindow->nameInput->getText());
		createFolderWindow->visible = false;
		createFolderWindow->enabled = false;
		showFolder(currentFolderPath);	
	}

	if(event->getDispatcher() == createFolderWindow->cancelButton) {
		createFolderWindow->visible = false;
		createFolderWindow->enabled = false;
	}


	if(event->getDispatcher() == newFolderButton) {
		createFolderWindow->nameInput->setText("");
		createFolderWindow->visible = true;
		createFolderWindow->enabled = true;
		
	}

	UIWindow::handleEvent(event);
}

UIFileDialog::~UIFileDialog() {
	if(!ownsChildren) {
		delete okButton;
		delete cancelButton;
		delete newFolderButton;
		delete scrollContainer;
		delete createFolderWindow;
		delete entryHolder;
		for(int i=0; i < sideBarEntries.size(); i++) {
			delete sideBarEntries[i];
		}
	}
}

CreateFolderWindow::CreateFolderWindow() : UIWindow("New folder name", 290, 80) {
	closeBtn->visible = false;
	closeBtn->enabled = false;

	nameInput = new UITextInput(false, 270, 16);
	addChild(nameInput);
	nameInput->setPosition(20, 34);

	cancelButton = new UIButton("Cancel", 100);
	addChild(cancelButton);
	cancelButton->setPosition(300-210, 80 - 12);

	okButton = new UIButton("OK",  100);
	addChild(okButton);
	okButton->setPosition(300-100, 80 - 12);
}

CreateFolderWindow::~CreateFolderWindow() {
	if(!ownsChildren) {
		delete cancelButton;
		delete okButton;
		delete nameInput;
	}
}
