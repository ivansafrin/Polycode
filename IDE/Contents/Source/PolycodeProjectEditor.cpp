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

PolycodeProjectEditor::PolycodeProjectEditor() : PolycodeEditor(true){

	grid = new ScreenImage("editorGrid.png");
	
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
	
	ScreenLabel *label2 = new ScreenLabel(L"DEFAULT VIDEO OPTIONS", fontSize+2, fontName, Label::ANTIALIAS_FULL);	
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 50);		

		
	label2 = new ScreenLabel(L"Width:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 80);		
	
	defaultWidthInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultWidthInput);
	defaultWidthInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	

	label2 = new ScreenLabel(L"Height:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 80, 80);		
	
	defaultHeightInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultHeightInput);
	defaultHeightInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());

	
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

	vSyncCheckBox = new UICheckBox("V-Sync", false);
	vSyncCheckBox->setPosition(padding, framerateInput->getPosition().y+framerateInput->getHeight()+10);
	mainSettingsWindow->addChild(vSyncCheckBox);
	
	label2 = new ScreenLabel(L"STARTUP OPTIONS", fontSize+2, fontName, Label::ANTIALIAS_FULL);	
	label2->setColor(1.0, 1.0, 1.0, 0.5);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, vSyncCheckBox->getPosition().y+vSyncCheckBox->getHeight()+30);		
	
	
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

	bgColorBox = new UIColorBox(Color(1.0, 0.5, 0.0, 0.9), 30,30);
	bgColorBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	mainSettingsWindow->addChild(bgColorBox);

}

PolycodeProjectEditor::~PolycodeProjectEditor() {
	
}

bool PolycodeProjectEditor::openFile(String filePath) {


	if(!configFile.loadFromXML(filePath)) {
		return false;
	}
	
	if(configFile.root["entryPoint"]) {	
		entryPointInput->setText(configFile.root["entryPoint"]->stringVal);
	} else {
		configFile.root.addChild("entryPoint", "Source/Main.lua");		
	}
	
	if(configFile.root["defaultWidth"]) {	
		defaultWidthInput->setText(configFile.root["defaultWidth"]->stringVal);
	} else {
		configFile.root.addChild("defaultWidth", 640);	
	}
	
	if(configFile.root["defaultHeight"]) {		
		defaultHeightInput->setText(configFile.root["defaultHeight"]->stringVal);
	} else {
		configFile.root.addChild("defaultHeight", 480);
	}

	if(configFile.root["vSync"]) {	
		vSyncCheckBox->setChecked(configFile.root["vSync"]->boolVal);
	} else {
		configFile.root.addChild("vSync", false);
	}

	

	unsigned int aaMap[7] = {0,1,1,1,2,2,3};
	if(configFile.root["antiAliasingLevel"]) {
		aaLevelComboBox->setSelectedIndex(aaMap[configFile.root["antiAliasingLevel"]->intVal]);
	} else {
		aaLevelComboBox->setSelectedIndex(0);
		configFile.root.addChild("antiAliasingLevel", 0);
	}

	unsigned int afMap[17] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5};
	if(configFile.root["anisotropyLevel"]) {
		afLevelComboBox->setSelectedIndex(afMap[configFile.root["anisotropyLevel"]->intVal]);
	} else {
		afLevelComboBox->setSelectedIndex(0);
		configFile.root.addChild("anisotropyLevel", 0);
	}

	if(configFile.root["frameRate"]) {
		framerateInput->setText(configFile.root["frameRate"]->stringVal);	
	} else {
		configFile.root.addChild("frameRate", 60);	
	}
	
	if(configFile.root["modules"]) {
		for(int i=0; i < configFile.root["modules"]->length; i++) {
			ObjectEntry *module = (*configFile.root["modules"])[i];
			for(int j=0; j < moduleCheckboxes.size(); j++) {
				if(moduleCheckboxes[j]->getCaptionLabel() == module->stringVal) {
					moduleCheckboxes[j]->setChecked(true);
				}
			}
		}
	}	

	Number backgroundColorR, backgroundColorG, backgroundColorB;	
	if(configFile.root["backgroundColor"]) {
		ObjectEntry *color = configFile.root["backgroundColor"];
		if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
			backgroundColorR = (*color)["red"]->NumberVal;
			backgroundColorG = (*color)["green"]->NumberVal;
			backgroundColorB = (*color)["blue"]->NumberVal;
			bgColorBox->setBoxColor(Color(backgroundColorR, backgroundColorG, backgroundColorB, 1.0));	
		} else {
			ObjectEntry *color = configFile.root.addChild("backgroundColor");
			color->addChild("red", 0.0);
			color->addChild("green", 0.0);
			color->addChild("blue", 0.0);						
		}
	}
	
	PolycodeEditor::openFile(filePath);	
	return true;
}

void PolycodeProjectEditor::Resize(int x, int y) {
	grid->setImageCoordinates(0,0,x,y);	
}

void PolycodeProjectEditor::saveFile() {

	configFile.root["frameRate"]->intVal = atoi(framerateInput->getText().c_str());
	configFile.root["defaultWidth"]->intVal = atoi(defaultWidthInput->getText().c_str());
	configFile.root["defaultHeight"]->intVal = atoi(defaultHeightInput->getText().c_str());	
	configFile.root["entryPoint"]->stringVal = entryPointInput->getText();
	
	ObjectEntry *color = configFile.root["backgroundColor"];	
	(*color)["red"]->NumberVal = bgColorBox->getSelectedColor().r;
	(*color)["green"]->NumberVal = bgColorBox->getSelectedColor().g;
	(*color)["blue"]->NumberVal = bgColorBox->getSelectedColor().b;


	if(configFile.root["modules"]) {
		configFile.root["modules"]->Clear();
	}
	
	for(int j=0; j < moduleCheckboxes.size(); j++) {
		if(moduleCheckboxes[j]->isChecked()) {
			
			if(!configFile.root["modules"]) {
				configFile.root.addChild("modules");	
			}
		
			configFile.root["modules"]->addChild("module", moduleCheckboxes[j]->getCaptionLabel());
		}
	}
	
	unsigned int afMap[6] = {0,1,2,4,8,16};
	unsigned int aaMap[4] = {0,2,4,6};
		
	configFile.root["antiAliasingLevel"]->intVal = aaMap[aaLevelComboBox->getSelectedIndex()];
	configFile.root["anisotropyLevel"]->intVal = afMap[afLevelComboBox->getSelectedIndex()];
	configFile.root["vSync"]->boolVal = vSyncCheckBox->isChecked();
	
	configFile.saveToXML(filePath);
}