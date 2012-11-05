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
#include "PolycodeConsole.h"

PolycodeProjectEditorFactory::PolycodeProjectEditorFactory(PolycodeProjectManager *projectManager) : PolycodeEditorFactory() {
	this->projectManager = projectManager;
	extensions.push_back("polyproject");
}

PolycodeEditor *PolycodeProjectEditorFactory::createEditor() {
	PolycodeProjectEditor *editor = new PolycodeProjectEditor(projectManager);
	return editor;
}

PolycodeProjectEditor::PolycodeProjectEditor(PolycodeProjectManager *projectManager) : PolycodeEditor(true){

	this->projectManager = projectManager;

	grid = new ScreenImage("Images/editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;
	
	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();	
	

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
		

	moduleSettingsWindow = new UIWindow("Project Modules", 300, 200);
	moduleSettingsWindow->setPosition(350,10);
	addChild(moduleSettingsWindow);
	
	Number lastYPos = 50;
	
	String polycodeBasePath = CoreServices::getInstance()->getCore()->getDefaultWorkingDirectory();
		
	std::vector<OSFileEntry> moduleFolders = OSBasics::parseFolder(polycodeBasePath+"/Standalone/Modules", false);
	for(int i=0; i < moduleFolders.size(); i++) {
		OSFileEntry entry = moduleFolders[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			UICheckBox *moduleCheckBox = new UICheckBox(entry.name, false);
			moduleCheckBox->setPosition(padding, lastYPos);
			lastYPos += moduleCheckBox->getHeight() + 5;
			moduleSettingsWindow->addChild(moduleCheckBox);
			moduleCheckboxes.push_back(moduleCheckBox);
		}
	}

	mainSettingsWindow = new UIWindow("Project Settings", 300, 420);
	mainSettingsWindow->setPosition(10,10);
	addChild(mainSettingsWindow);
	
	ScreenLabel *label2 = new ScreenLabel(L"DEFAULT VIDEO OPTIONS", 22, "section", Label::ANTIALIAS_FULL);	
	label2->setColor(1.0, 1.0, 1.0, 0.4);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 40);		

		
	label2 = new ScreenLabel(L"Width:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 80);		
	
	defaultWidthInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultWidthInput);
	defaultWidthInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	defaultWidthInput->setNumberOnly(true);

	label2 = new ScreenLabel(L"Height:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 80, 80);		
	
	defaultHeightInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultHeightInput);
	defaultHeightInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	defaultHeightInput->setNumberOnly(true);
	
	label2 = new ScreenLabel(L"Anti-aliasing:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 160, 80);		
	
	aaLevelComboBox = new UIComboBox(120);		
	aaLevelComboBox->addComboItem("No AA");
	aaLevelComboBox->addComboItem("2x MSAA");
	aaLevelComboBox->addComboItem("4x MSAA");
	aaLevelComboBox->addComboItem("6x MSAA");			
	aaLevelComboBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());

	label2 = new ScreenLabel(L"Anisotropic filtering:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, defaultHeightInput->getPosition().y+defaultHeightInput->getHeight()+10);		
	
	afLevelComboBox = new UIComboBox(250);		
	afLevelComboBox->addComboItem("No Anisotropic Filtering");
	afLevelComboBox->addComboItem("1x Anisotropic Filtering");
	afLevelComboBox->addComboItem("2x Anisotropic Filtering");
	afLevelComboBox->addComboItem("4x Anisotropic Filtering");
	afLevelComboBox->addComboItem("8x Anisotropic Filtering");
	afLevelComboBox->addComboItem("16x Anisotropic Filtering");			
	afLevelComboBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());

	label2 = new ScreenLabel(L"Framerate:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, afLevelComboBox->getPosition().y+afLevelComboBox->getHeight()+10);		
	
	framerateInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(framerateInput);
	framerateInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	framerateInput->setNumberOnly(true);

	vSyncCheckBox = new UICheckBox("V-Sync", false);
	vSyncCheckBox->setPosition(padding, framerateInput->getPosition().y+framerateInput->getHeight()+10);
	mainSettingsWindow->addChild(vSyncCheckBox);
	
	label2 = new ScreenLabel(L"STARTUP OPTIONS", 22, "section", Label::ANTIALIAS_FULL);	
	label2->setColor(1.0, 1.0, 1.0, 0.4);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, vSyncCheckBox->getPosition().y+vSyncCheckBox->getHeight()+20);		
	
	
	label2 = new ScreenLabel(L"Entry point file:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, vSyncCheckBox->getPosition().y+vSyncCheckBox->getHeight()+60);		
	
	entryPointInput = new UITextInput(false, 200, 12);	
	mainSettingsWindow->addChild(entryPointInput);
	entryPointInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());


	mainSettingsWindow->addChild(afLevelComboBox);			
	mainSettingsWindow->addChild(aaLevelComboBox);		


	label2 = new ScreenLabel(L"Background color:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, entryPointInput->getPosition().y+entryPointInput->getHeight()+10);		

	colorPicker = new UIColorPicker();
	colorPicker->setPosition(200,200);
	addChild(colorPicker);

	bgColorBox = new UIColorBox(colorPicker, Color(1.0, 0.5, 0.0, 0.9), 30,30);
	bgColorBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	mainSettingsWindow->addChild(bgColorBox);
	
	

}

PolycodeProjectEditor::~PolycodeProjectEditor() {
	
}

bool PolycodeProjectEditor::openFile(OSFileEntry filePath) {	
	
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
	return true;
}

void PolycodeProjectEditor::Resize(int x, int y) {
	grid->setImageCoordinates(0,0,x,y);	
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
		
	unsigned int afMap[6] = {0,1,2,4,8,16};
	unsigned int aaMap[4] = {0,2,4,6};
		
	associatedProject->data.aaLevel = aaMap[aaLevelComboBox->getSelectedIndex()];
	associatedProject->data.anisotropy = afMap[afLevelComboBox->getSelectedIndex()];
	associatedProject->data.vSync = vSyncCheckBox->isChecked();
	
	associatedProject->saveFile();
}