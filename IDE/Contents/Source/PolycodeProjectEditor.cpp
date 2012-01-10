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
		
	ScreenLabel *label2 = new ScreenLabel(L"Width:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, 50);		
	
	defaultWidthInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultWidthInput);
	defaultWidthInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	

	label2 = new ScreenLabel(L"Height:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 80, 50);		
	
	defaultHeightInput = new UITextInput(false, 60, 12);	
	mainSettingsWindow->addChild(defaultHeightInput);
	defaultHeightInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());

	
	label2 = new ScreenLabel(L"Anti-aliasing:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding + 160, 50);		
	
/*
	aaLevelComboBox = new UIComboBox(100);		
	mainSettingsWindow->addChild(aaLevelComboBox);	
	aaLevelComboBox->addComboItem("No AA");
	aaLevelComboBox->addComboItem("2x MSAA");
	aaLevelComboBox->addComboItem("4x MSAA");
	aaLevelComboBox->addComboItem("6x MSAA");			
	aaLevelComboBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
*/
	
//	aaLevelInput = new UIHSlider(0,6, 100);
//	mainSettingsWindow->addChild(aaLevelInput);
//	aaLevelInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());


	vSyncCheckBox = new UICheckBox("V-Sync", false);
	vSyncCheckBox->setPosition(padding, defaultHeightInput->getPosition().y+defaultHeightInput->getHeight()+10);
	mainSettingsWindow->addChild(vSyncCheckBox);
	
	label2 = new ScreenLabel(L"Entry point file:", fontSize, fontName, Label::ANTIALIAS_FULL);
	mainSettingsWindow->addChild(label2);
	label2->setPosition(padding, vSyncCheckBox->getPosition().y+vSyncCheckBox->getHeight()+10);		
	
	entryPointInput = new UITextInput(false, 200, 12);	
	mainSettingsWindow->addChild(entryPointInput);
	entryPointInput->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	
	
}

PolycodeProjectEditor::~PolycodeProjectEditor() {
	
}

bool PolycodeProjectEditor::openFile(String filePath) {
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeProjectEditor::Resize(int x, int y) {
}

void PolycodeProjectEditor::saveFile() {

}