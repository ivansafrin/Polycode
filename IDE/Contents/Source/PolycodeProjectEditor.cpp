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
 
#include "PolycodeProjectEditor.h"
#include "OSBasics.h"
#include "PolycodeFrame.h"
#include "PolycodeConsole.h"

extern UIColorPicker *globalColorPicker;
extern UIGlobalMenu *globalMenu;
extern PolycodeFrame *globalFrame;

PolycodeProjectEditorFactory::PolycodeProjectEditorFactory(PolycodeProjectManager *projectManager) : PolycodeEditorFactory() {
	this->projectManager = projectManager;
	extensions.push_back("polyproject");
}

PolycodeEditor *PolycodeProjectEditorFactory::createEditor() {
	PolycodeProjectEditor *editor = new PolycodeProjectEditor(projectManager);
	return editor;
}

ProjectFontEntry::ProjectFontEntry(String fontPath, String fontName) : UIElement() {

	this->fontPath = fontPath;

	removeButton = new UIImageButton("Images/remove_icon.png");
	removeButton->setPosition(0, 5);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(removeButton);

	fontNameInput = new UITextInput(false, 100, 13);
	fontNameInput->setText(fontName);
	fontNameInput->setPosition(20, 0);
	fontNameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(fontNameInput);

	OSFileEntry entry = OSFileEntry(fontPath, OSFileEntry::TYPE_FILE);

	fontFileLabel = new ScreenLabel(entry.name, 12);
	fontFileLabel->color.a = 0.6;
	addChild(fontFileLabel);
	fontFileLabel->setPosition(140, 3);

	CoreServices::getInstance()->getFontManager()->registerFont(fontName, fontPath);
}

void ProjectFontEntry::handleEvent(Event *event) {
	if(event->getDispatcher() == fontNameInput && event->getEventCode() == UIEvent::CHANGE_EVENT && event->getEventType() == "UIEvent") {
		FontEntry *entry = CoreServices::getInstance()->getFontManager()->getFontEntryByFontPath(fontPath);
		if(entry) {
			entry->fontName = fontNameInput->getText();
		}
	}

	if(event->getDispatcher() == removeButton && event->getEventCode() == UIEvent::CLICK_EVENT && event->getEventType() == "UIEvent") {
		FontEntry *entry = CoreServices::getInstance()->getFontManager()->getFontEntryByFontPath(fontPath);
		CoreServices::getInstance()->getFontManager()->removeFontEntry(entry, false);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

ProjectFontEntry::~ProjectFontEntry() {

}

PolycodeProjectEditor::PolycodeProjectEditor(PolycodeProjectManager *projectManager) : PolycodeEditor(true){

	isLoading = true;

	this->projectManager = projectManager;


	Config *conf = CoreServices::getInstance()->getConfig();
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");


	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));

	ScreenLabel *label = new ScreenLabel("PROJECT SETTINGS", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));

	addChild(label);
	label->setPosition(10, 3);

	moduleSettingsWindow = new UIElement();
	moduleSettingsWindow->setPosition(350,10);
	addChild(moduleSettingsWindow);


	Number lastYPos = 40;

	label = new ScreenLabel("PROJECT MODULES", 18, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	moduleSettingsWindow->addChild(label);
	label->setPosition(0, lastYPos);

	lastYPos += 40;

	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();

	std::vector<OSFileEntry> moduleFolders = OSBasics::parseFolder(polycodeBasePath+"/Standalone/Modules", false);
	for(int i=0; i < moduleFolders.size(); i++) {
		OSFileEntry entry = moduleFolders[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UICheckBox *moduleCheckBox = new UICheckBox(entry.name, false);
			moduleCheckBox->setPosition(0, lastYPos);
			lastYPos += moduleCheckBox->getHeight() + 5;
			moduleSettingsWindow->addChild(moduleCheckBox);
			moduleCheckboxes.push_back(moduleCheckBox);
		}
	}

	lastYPos += 20;

	label = new ScreenLabel("PROJECT FONTS", 18, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	moduleSettingsWindow->addChild(label);
	label->setPosition(0, lastYPos);

	lastYPos += 30;

	fontEntryBase = new UIElement();
	moduleSettingsWindow->addChild(fontEntryBase);	
	fontEntryBase->setPosition(0, lastYPos);

	addFontButton = new UIButton("Add Font", 100);
	fontEntryBase->addChild(addFontButton);
	addFontButton->addEventListener(this, UIEvent::CLICK_EVENT);

	mainSettingsWindow = new UIElement();
	mainSettingsWindow->setPosition(0,10);
	addChild(mainSettingsWindow);

	ScreenLabel *label2 = new ScreenLabel(L"DEFAULT VIDEO OPTIONS", 18, "section", Label::ANTIALIAS_FULL);	
	label2->setColor(1.0, 1.0, 1.0, 0.4);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 40);


	label2 = new ScreenLabel(L"Width", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 6, 80);

	defaultWidthInput = new UITextInput(false, 60, 12);
	mainSettingsWindow->addChild(defaultWidthInput);
	defaultWidthInput->setPosition(label2->getPosition().x-6, label2->getPosition().y+18);
	defaultWidthInput->setNumberOnly(true);

	label2 = new ScreenLabel(L"Height", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 80 + 6, 80);

	defaultHeightInput = new UITextInput(false, 60, 12);
	mainSettingsWindow->addChild(defaultHeightInput);
	defaultHeightInput->setPosition(label2->getPosition().x-6, label2->getPosition().y+18);
	defaultHeightInput->setNumberOnly(true);

	label2 = new ScreenLabel(L"Anti-aliasing", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 160 + 6, 80);

	aaLevelComboBox = new UIComboBox(globalMenu, 120);
	aaLevelComboBox->addComboItem("No AA");
	aaLevelComboBox->addComboItem("2x MSAA");
	aaLevelComboBox->addComboItem("4x MSAA");
	aaLevelComboBox->addComboItem("6x MSAA");
	aaLevelComboBox->setPosition(label2->getPosition().x-6, label2->getPosition().y+18);

	label2 = new ScreenLabel(L"Texture filtering mode:", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 6, defaultHeightInput->getPosition().y+30);

	texFilteringComboBox = new UIComboBox(globalMenu, 280);
	texFilteringComboBox->addComboItem("Nearest Neighbor");
	texFilteringComboBox->addComboItem("Linear");
	texFilteringComboBox->setPosition(label2->getPosition().x - 6, label2->getPosition().y+18);


	label2 = new ScreenLabel(L"Anisotropic filtering:", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 6, texFilteringComboBox->getPosition().y+30);

	afLevelComboBox = new UIComboBox(globalMenu, 280);
	afLevelComboBox->addComboItem("No Anisotropic Filtering");
	afLevelComboBox->addComboItem("1x Anisotropic Filtering");
	afLevelComboBox->addComboItem("2x Anisotropic Filtering");
	afLevelComboBox->addComboItem("4x Anisotropic Filtering");
	afLevelComboBox->addComboItem("8x Anisotropic Filtering");
	afLevelComboBox->addComboItem("16x Anisotropic Filtering");
	afLevelComboBox->setPosition(label2->getPosition().x-6, label2->getPosition().y+18);

	label2 = new ScreenLabel(L"Framerate", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 6, afLevelComboBox->getPosition().y+30);

	framerateInput = new UITextInput(false, 60, 12);
	mainSettingsWindow->addChild(framerateInput);
	framerateInput->setPosition(label2->getPosition().x-6, label2->getPosition().y+18);
	framerateInput->setNumberOnly(true);

	vSyncCheckBox = new UICheckBox("V-Sync", false);
	vSyncCheckBox->setPosition(label2->getPosition().x + 80, label2->getPosition().y+18);
	mainSettingsWindow->addChild(vSyncCheckBox);

	label2 = new ScreenLabel(L"STARTUP OPTIONS", 18, "section", Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.4);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, vSyncCheckBox->getPosition().y+vSyncCheckBox->getHeight()+20);


	label2 = new ScreenLabel(L"Entry point file", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 6, vSyncCheckBox->getPosition().y+80);

	entryPointInput = new UITextInput(false, 200, 12);
	mainSettingsWindow->addChild(entryPointInput);
	entryPointInput->setPosition(label2->getPosition().x - 6, label2->getPosition().y+18);


	mainSettingsWindow->addChild(afLevelComboBox);
	mainSettingsWindow->addChild(aaLevelComboBox);
	mainSettingsWindow->addChild(texFilteringComboBox);

	label2 = new ScreenLabel(L"Background color:", fontSize, fontName, Label::ANTIALIAS_FULL);
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, entryPointInput->getPosition().y+entryPointInput->getHeight()+10);


	bgColorBox = new UIColorBox(globalColorPicker, Color(1.0, 0.5, 0.0, 0.9), 30,30);
	bgColorBox->setPosition(label2->getPosition().x, label2->getPosition().y+18);
	mainSettingsWindow->addChild(bgColorBox);

	vSyncCheckBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	defaultWidthInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	defaultHeightInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	framerateInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	aaLevelComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	afLevelComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	texFilteringComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	entryPointInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	bgColorBox->addEventListener(this, UIEvent::CHANGE_EVENT);

	isLoading = false;
}

PolycodeProjectEditor::~PolycodeProjectEditor() {

}

void PolycodeProjectEditor::refreshFontEntries() {
	for(int i=0; i < fontEntries.size(); i++) {
		fontEntries[i]->setPosition(0, 30*i);
	}
	addFontButton->setPosition(0, (fontEntries.size() * 30) + 10);
	if(!isLoading) {
		setHasChanges(true);
	}
}

void PolycodeProjectEditor::handleEvent(Event *event) {

	if(event->getEventType() == "UIEvent" 
			&& (event->getDispatcher() == vSyncCheckBox || event->getDispatcher() == defaultWidthInput || event->getDispatcher() == defaultHeightInput 
				|| event->getDispatcher() == framerateInput || event->getDispatcher() == aaLevelComboBox || event->getDispatcher() == afLevelComboBox 
				|| event->getDispatcher() == texFilteringComboBox  || event->getDispatcher() == entryPointInput || event->getDispatcher() == bgColorBox) 
			&& !isLoading) {
		setHasChanges(true);
	}

	if(event->getDispatcher() == addFontButton && event->getEventCode() == UIEvent::CLICK_EVENT && event->getEventType() == "UIEvent") {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);

		std::vector<String> extensions;
		extensions.push_back("ttf");
		extensions.push_back("otf");
		globalFrame->showAssetBrowser(extensions);
	} else if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String newFontPath = globalFrame->assetBrowser->getSelectedAssetPath();

		newFontPath = newFontPath.replace(parentProject->getRootFolder()+"/", "");

		bool hasFont = false;
		for(int i=0; i < fontEntries.size(); i++) {
			if(fontEntries[i]->fontPath == newFontPath) {
				hasFont = true;
				break;
			}
		}

		if(!hasFont) {
			ProjectFontEntry *newEntry = new ProjectFontEntry(newFontPath, "font_name");
			newEntry->addEventListener(this, Event::CHANGE_EVENT);
			fontEntryBase->addChild(newEntry);
			fontEntries.push_back(newEntry);
			refreshFontEntries();
		}

		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
		globalFrame->hideModal();

	}

	bool doRefresh = false;
	for(int i=0; i < fontEntries.size(); i++) {
		if(event->getDispatcher() == fontEntries[i]) {
			fontEntryBase->removeChild(fontEntries[i]);
			fontEntries.erase(fontEntries.begin()+i);
			doRefresh = true;
			break;
		}
	}

	if(doRefresh) {
		refreshFontEntries();
	}
}

bool PolycodeProjectEditor::openFile(OSFileEntry filePath) {
	isLoading = true;
	associatedProject = projectManager->getProjectByProjectFile(filePath.fullPath);
	if(!associatedProject) {
		return false;
	}

	entryPointInput->setText(associatedProject->data.entryPoint);
	defaultWidthInput->setText(String::IntToString(associatedProject->data.defaultWidth));
	defaultHeightInput->setText(String::IntToString(associatedProject->data.defaultHeight));
	vSyncCheckBox->setChecked(associatedProject->data.vSync);

	unsigned int aaMap[7] = {0,1,1,1,2,2,3};
	aaLevelComboBox->setSelectedIndex(aaMap[associatedProject->data.aaLevel]);

	unsigned int afMap[17] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5};
	afLevelComboBox->setSelectedIndex(afMap[associatedProject->data.anisotropy]);
	framerateInput->setText(String::IntToString(associatedProject->data.frameRate));

	if(associatedProject->data.filteringMode == "nearest") {
		texFilteringComboBox->setSelectedIndex(0);
	} else {
		texFilteringComboBox->setSelectedIndex(1);
	}

	for(int i=0; i < associatedProject->data.fonts.size(); i++) {
		ProjectFontData fontData = associatedProject->data.fonts[i];

		ProjectFontEntry *newEntry = new ProjectFontEntry(fontData.fontPath, fontData.fontName);
		newEntry->addEventListener(this, Event::CHANGE_EVENT);
		fontEntryBase->addChild(newEntry);
		fontEntries.push_back(newEntry);

	}

	for(int i=0; i < associatedProject->data.modules.size(); i++) {
		bool hasModule = false;
		for(int j=0; j < moduleCheckboxes.size(); j++) {
			if(moduleCheckboxes[j]->getCaptionLabel() == associatedProject->data.modules[i]) {
				moduleCheckboxes[j]->setChecked(true);
				hasModule = true;
			}
		}
		if(!hasModule) {
			PolycodeConsole::print("WARNING: MISSING MODULE: "+associatedProject->data.modules[i]);
		}
	}

	bgColorBox->setBoxColor(Color(associatedProject->data.backgroundColorR, associatedProject->data.backgroundColorG, associatedProject->data.backgroundColorB, 1.0));

	PolycodeEditor::openFile(filePath);
	refreshFontEntries();
	isLoading = false;
	return true;
}

void PolycodeProjectEditor::Resize(int x, int y) {

	headerBg->setShapeSize(x, 30);

	PolycodeEditor::Resize(x,y);
}


void PolycodeProjectEditor::saveFile() {

	if(!associatedProject) {
		return;
	}

	associatedProject->data.frameRate = atoi(framerateInput->getText().c_str());
	associatedProject->data.defaultWidth = atoi(defaultWidthInput->getText().c_str());
	associatedProject->data.defaultHeight = atoi(defaultHeightInput->getText().c_str());
	associatedProject->data.entryPoint = entryPointInput->getText();

	associatedProject->data.backgroundColorR = bgColorBox->getSelectedColor().r;
	associatedProject->data.backgroundColorG = bgColorBox->getSelectedColor().g;
	associatedProject->data.backgroundColorB = bgColorBox->getSelectedColor().b;

	associatedProject->data.modules.clear();

	for(int j=0; j < moduleCheckboxes.size(); j++) {
		if(moduleCheckboxes[j]->isChecked()) {
			associatedProject->data.modules.push_back(moduleCheckboxes[j]->getCaptionLabel());
		}
	}

	associatedProject->data.fonts.clear();

	for(int j=0; j < fontEntries.size(); j++) {
		ProjectFontData fontData = ProjectFontData(fontEntries[j]->fontNameInput->getText(), fontEntries[j]->fontPath);
		associatedProject->data.fonts.push_back(fontData);
	}

	unsigned int afMap[6] = {0,1,2,4,8,16};
	unsigned int aaMap[4] = {0,2,4,6};
	String filteringMap[2] = {"nearest", "linear"};

	associatedProject->data.filteringMode = filteringMap[texFilteringComboBox->getSelectedIndex()];
	associatedProject->data.aaLevel = aaMap[aaLevelComboBox->getSelectedIndex()];
	associatedProject->data.anisotropy = afMap[afLevelComboBox->getSelectedIndex()];
	associatedProject->data.vSync = vSyncCheckBox->isChecked();

	associatedProject->saveFile();
	setHasChanges(false);
}
