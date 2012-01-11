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

PolycodeProjectEditor::PolycodeProjectEditor() : PolycodeEditor(true){
	mainSettingsWindow = new UIWindow("Project Settings", 300, 500);
	mainSettingsWindow->setPosition(10,10);
	addChild(mainSettingsWindow);
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
		
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

	Object configFile;
	if(!configFile.loadFromXML(filePath)) {
		return false;
	}
	
	if(configFile.root["entryPoint"]) {	
		entryPointInput->setText(configFile.root["entryPoint"]->stringVal);
	}
	
	if(configFile.root["defaultWidth"]) {	
		defaultWidthInput->setText(configFile.root["defaultWidth"]->stringVal);
	}
	if(configFile.root["defaultHeight"]) {		
		defaultHeightInput->setText(configFile.root["defaultHeight"]->stringVal);
	}

	unsigned int aaMap[7] = {0,1,1,1,2,2,3};
	if(configFile.root["antiAliasingLevel"]) {
		aaLevelComboBox->setSelectedIndex(aaMap[configFile.root["antiAliasingLevel"]->intVal]);
	} else {
		aaLevelComboBox->setSelectedIndex(0);
	}

	unsigned int afMap[17] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5};
	if(configFile.root["anisotropyLevel"]) {
		afLevelComboBox->setSelectedIndex(afMap[configFile.root["anisotropyLevel"]->intVal]);
	} else {
		afLevelComboBox->setSelectedIndex(0);
	}


	if(configFile.root["frameRate"]) {
		framerateInput->setText(configFile.root["frameRate"]->stringVal);	
	}
/*
	if(configFile.root["backgroundColor"]) {
		ObjectEntry *color = configFile.root["backgroundColor"];
		if((*color)["red"] && (*color)["green"] && (*color)["blue"]) {
			backgroundColorR = (*color)["red"]->NumberVal;
			backgroundColorG = (*color)["green"]->NumberVal;
			backgroundColorB = (*color)["blue"]->NumberVal;
			printf("Background color: %f %f %f\n", backgroundColorR, backgroundColorG, backgroundColorB);

		} else {
			printf("backgroundColor node specified, but missing all three color attributes (red,green,blue). Ignoring.\n");
		}
	}*/
	
	PolycodeEditor::openFile(filePath);	
	return true;
}

void PolycodeProjectEditor::Resize(int x, int y) {
}

void PolycodeProjectEditor::saveFile() {

}