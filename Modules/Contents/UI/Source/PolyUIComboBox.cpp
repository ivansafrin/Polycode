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

#include "PolyUIComboBox.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include "PolyConfig.h"
#include "PolyRenderer.h"

using namespace Polycode;

UIComboBoxItem::UIComboBoxItem(String label, void *data) {
	this->label = label;
	this->data = data;
}

UIComboBoxItem::~UIComboBoxItem() {

}

UIComboBox::UIComboBox(UIGlobalMenu *globalMenu, Number comboWidth) : UIElement() {

	this->globalMenu = globalMenu;

	selectedIndex = -1;

	Config *conf = CoreServices::getInstance()->getConfig();
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
	
	String fontName = conf->getStringValue("Polycode", "uiComboBoxFont");
	int fontSize = conf->getNumericValue("Polycode", "uiComboBoxFontSize");	
	String dropDownImageFile = conf->getStringValue("Polycode", "uiComboBoxDropdownImage");
	String bgImage = conf->getStringValue("Polycode", "uiComboBoxBgImage");	

	Number st = conf->getNumericValue("Polycode", "uiComboBoxBgT");
	Number sr = conf->getNumericValue("Polycode", "uiComboBoxBgR");
	Number sb = conf->getNumericValue("Polycode", "uiComboBoxBgB");
	Number sl = conf->getNumericValue("Polycode", "uiComboBoxBgL");
	
	Number paddingX = conf->getNumericValue("Polycode", "uiComboBoxTextOffsetX");	
	Number paddingY = conf->getNumericValue("Polycode", "uiComboBoxTextOffsetY");	

	dropDownX = conf->getNumericValue("Polycode", "uiComboBoxDropX");
	dropDownY = conf->getNumericValue("Polycode", "uiComboBoxDropY");
		
	dropDownImage = new UIImage(dropDownImageFile);
    dropDownImage->Resize(dropDownImage->getWidth() / uiScale, dropDownImage->getHeight() / uiScale);
    
	dropDownImage->setPosition(comboWidth - dropDownImage->getWidth() - dropDownX,dropDownY);
	
	this->comboHeight = conf->getNumericValue("Polycode", "uiComboBoxHeight");
	this->comboWidth = comboWidth;
	nextItemHeight = 0;
	
	bgBox = new UIBox(bgImage, st,sr,sb,sl, comboWidth, comboHeight);	

	addChild(bgBox);
	addChild(dropDownImage);
	
	selectedLabel = new UILabel("<None>", fontSize, fontName);
    selectedLabel->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	selectedLabel->setPosition(paddingX, paddingY);
	addChild(selectedLabel);
	
	selectedLabel->color.setColorHexFromString(conf->getStringValue("Polycode", "uiDefaultFontColor"));
	
	String selectorBgImage = conf->getStringValue("Polycode", "uiComboBoxSelectorBgImage");	
	
	st = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgT");
	sr = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgR");
	sb = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgB");
	sl = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgL");
	
	dropDownMenu = NULL;
	
	selectedOffset = 0;

	dropDownImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	dropDownImage->setAnchorPoint(-1.0, -1.0, 0.0);
	dropDownImage->processInputEvents = true;	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	bgBox->processInputEvents = true;	
				
	setWidth(comboWidth);
	setHeight(comboHeight);
}

void UIComboBox::Resize(Number width, Number height) {
	this->comboWidth = width;
	bgBox->resizeBox(width, comboHeight);
	setWidth(width);
	setHeight(height);	
	matrixDirty = true;	
	dropDownImage->setPosition(comboWidth - dropDownImage->getWidth() - dropDownX,dropDownY);	
}

UIComboBox::~UIComboBox() {
	for(int c = 0; c < items.size(); c++)
		delete items[c];
	
	if(!ownsChildren) {
		delete dropDownImage;
		delete bgBox;
		delete selectedLabel;
	}
}

void UIComboBox::clearItems() {
	items.clear();
	selectedLabel->setText("<None>");
}
			
int UIComboBox::addComboItem(String itemName, void *data) {
	UIComboBoxItem *newItem = new UIComboBoxItem(itemName, data);
	items.push_back(newItem);
	return items.size()-1;
}

int UIComboBox::addComboItem(String itemName) {
	return addComboItem(itemName, NULL);
}

UIComboBoxItem *UIComboBox::getSelectedItem() {
	if(selectedIndex < items.size()) {
		return items[selectedIndex];
	} else {
		return NULL;
	}
}

void UIComboBox::toggleDropDown() {
	Vector2 screenPos = this->getScreenPositionForMainCamera();
	dropDownMenu = globalMenu->showMenu(screenPos.x, screenPos.y, getWidth());
	
	for(int i=0; i < items.size(); i++) {
		dropDownMenu->addOption(items[i]->label, String::IntToString(i));
	}
	
	dropDownMenu->addEventListener(this, UIEvent::OK_EVENT);
}

int UIComboBox::getSelectedIndex() {
	return selectedIndex;
}

void UIComboBox::setSelectedIndex(unsigned int newIndex, bool suppressChangeEvent) {
	if(newIndex < items.size()) {
		selectedIndex = newIndex;				
		selectedLabel->setText(items[selectedIndex]->label);
		if(!suppressChangeEvent) {
			dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
		}
	}
}

unsigned int UIComboBox::getNumItems() {
	return items.size();
}

UIComboBoxItem *UIComboBox::getItemAtIndex(unsigned int index) {
	return items[index];
}
				
void UIComboBox::handleEvent(Event *event) {
	
	if(event->getDispatcher() == dropDownMenu && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		setSelectedIndex(atoi(dropDownMenu->getSelectedItem()->_id.c_str()));
	}

	if(event->getDispatcher() == dropDownImage || event->getDispatcher() == bgBox) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				toggleDropDown();
			break;
		}
	}
    
    UIElement::handleEvent(event);    
}
