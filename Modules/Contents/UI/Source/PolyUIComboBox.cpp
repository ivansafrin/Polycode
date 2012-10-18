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

using namespace Polycode;

UIComboBoxItem::UIComboBoxItem(String label, Number comboWidth, Number comboHeight) : UIElement() {
	this->label = label;
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	String fontName = conf->getStringValue("Polycode", "uiComboBoxFont");
	int fontSize = conf->getNumericValue("Polycode", "uiComboBoxFontSize");	

	Number paddingX = conf->getNumericValue("Polycode", "uiComboBoxTextOffsetX");	
	Number paddingY = conf->getNumericValue("Polycode", "uiComboBoxTextOffsetY");	

	itemLabel = new ScreenLabel(label, fontSize, fontName);
	itemLabel->setPosition(paddingX, floor(((comboHeight/2.0) - itemLabel->getHeight()/2.0) + paddingY));	
	addChild(itemLabel);
	
}

UIComboBoxItem::~UIComboBoxItem() {

}


UIComboBox::UIComboBox(Number comboWidth) : UIElement() {

	isDroppedDown = false;
	selectedIndex = -1;

	Config *conf = CoreServices::getInstance()->getConfig();	
	
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
		
	dropDownImage = new ScreenImage(dropDownImageFile);
	dropDownImage->setPosition(comboWidth - dropDownImage->getWidth(),0);
	
	this->comboHeight = dropDownImage->getHeight();
	this->comboWidth = comboWidth;
	nextItemHeight = 0;
	
	bgBox = new UIBox(bgImage, st,sr,sb,sl, comboWidth, comboHeight);	

	addChild(bgBox);
	addChild(dropDownImage);
	
	selectedLabel = new ScreenLabel("<None>", fontSize, fontName);
	selectedLabel->setPosition(paddingX, floor(((dropDownImage->getHeight()/2.0) - selectedLabel->getHeight()/2.0) + paddingY));
	addChild(selectedLabel);
	
	String dropdownBgImage = conf->getStringValue("Polycode", "uiComboBoxItemsBgImage");	
	
	st = conf->getNumericValue("Polycode", "uiComboBoxDropdownBgT");
	sr = conf->getNumericValue("Polycode", "uiComboBoxDropdownBgR");
	sb = conf->getNumericValue("Polycode", "uiComboBoxDropdownBgB");
	sl = conf->getNumericValue("Polycode", "uiComboBoxDropdownBgL");
	
	dropDownBox = new UIBox(dropdownBgImage, st,sr,sb,sl, comboWidth, comboHeight);
	dropDownBox->setPosition(0,comboHeight);	
	addChild(dropDownBox);
	
	String selectorBgImage = conf->getStringValue("Polycode", "uiComboBoxSelectorBgImage");	
	
	st = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgT");
	sr = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgR");
	sb = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgB");
	sl = conf->getNumericValue("Polycode", "uiComboBoxSelectorBgL");
	
	dropDownBox->blockMouseInput = true;
	
	selectorBox = new UIBox(selectorBgImage, st,sr,sb,sl, comboWidth, comboHeight);
	dropDownBox->addChild(selectorBox);
	selectorBox->blockMouseInput = true;
	
	selectedOffset = 0;
	dropDownBox->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	dropDownBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	dropDownBox->processInputEvents = true;

	dropDownImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	dropDownImage->processInputEvents = true;	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	bgBox->processInputEvents = true;	
			
	isDroppedDown = false;
	updateVis();
	
	this->width = comboWidth;
	this->height = comboHeight;
}

UIComboBox::~UIComboBox() {

}

int UIComboBox::addComboItem(String itemName) {
	UIComboBoxItem *newItem = new UIComboBoxItem(itemName, comboWidth, comboHeight);
	items.push_back(newItem);
	dropDownBox->addChild(newItem);
	newItem->setPosition(0,nextItemHeight);
	nextItemHeight += comboHeight;
	dropDownBox->resizeBox(comboWidth, nextItemHeight);
	return items.size()-1;
}

void UIComboBox::toggleDropDown() {
	isDroppedDown = !isDroppedDown;
	updateVis();
}

void UIComboBox::updateVis() {
	dropDownBox->visible = isDroppedDown;
	dropDownBox->enabled = isDroppedDown;	
}

int UIComboBox::getSelectedIndex() {
	return selectedIndex;
}

void UIComboBox::setSelectedIndex(unsigned int newIndex) {
	if(newIndex < items.size()) {
		selectedIndex = newIndex;				
		selectedLabel->setText(items[selectedIndex]->label);		
	}
}
				
void UIComboBox::handleEvent(Event *event) {

	if(event->getDispatcher() == dropDownBox) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
			{
				InputEvent *inputEvent = (InputEvent*) event;
				selectedOffset = floor(inputEvent->getMousePosition().y/comboHeight);
				if(selectedOffset < 0)
					selectedOffset = 0;
					
				if(selectedOffset >= 0 && selectedOffset < items.size())
					selectorBox->setPosition(0,selectedOffset*comboHeight);
			}				
			break;
			case InputEvent::EVENT_MOUSEDOWN:
			{
				selectedIndex = selectedOffset;				
				selectedLabel->setText(items[selectedIndex]->label);				
				isDroppedDown = false;
				updateVis();				
			}
			break;
		}	
	}
	
	if(event->getDispatcher() == dropDownImage || event->getDispatcher() == bgBox) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				toggleDropDown();
			break;
		}
	}
}
