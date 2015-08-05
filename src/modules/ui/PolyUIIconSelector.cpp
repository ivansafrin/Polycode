/*
 Copyright (C) 2014 by Ivan Safrin
 
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

#include "PolyUIIconSelector.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyCoreServices.h"


UIIconSelector::UIIconSelector(Number height) : UIElement() {
    
	Config *conf = CoreServices::getInstance()->getConfig();
	
	Number st = conf->getNumericValue("Polycode", "uiIconSelectorBgT");
	Number sr = conf->getNumericValue("Polycode", "uiIconSelectorBgR");
	Number sb = conf->getNumericValue("Polycode", "uiIconSelectorBgB");
	Number sl = conf->getNumericValue("Polycode", "uiIconSelectorBgL");

	paddingX = conf->getNumericValue("Polycode", "uiIconSelectorPaddingX");
	paddingY = conf->getNumericValue("Polycode", "uiIconSelectorPaddingY");
    
	bgRect = new UIBox(conf->getStringValue("Polycode", "uiIconSelectorBg"),
						   st,sr,sb,sl,
						   10, 10);
    addChild(bgRect);
    
    selectorSize = height;
    if(selectorSize == 0.0) {
        selectorSize = conf->getNumericValue("Polycode", "uiIconSelectorDefaultSize");
    }
    
    st = conf->getNumericValue("Polycode", "uiIconSelectorBoxT");
    sr = conf->getNumericValue("Polycode", "uiIconSelectorBoxR");
    sb = conf->getNumericValue("Polycode", "uiIconSelectorBoxB");
    sl = conf->getNumericValue("Polycode", "uiIconSelectorBoxL");
    
    selectorRect = new UIBox(conf->getStringValue("Polycode", "uiIconSelectorBox"),
                             st,sr,sb,sl,
                             selectorSize, selectorSize);
    addChild(selectorRect);
    selectorRect->visible = false;
    resetSize();
    
}

void UIIconSelector::addIcon(String fileName) {
    UIImageButton *newIcon = new UIImageButton(fileName, 1.0, selectorSize, selectorSize);
    icons.push_back(newIcon);
    addChild(newIcon);
    newIcon->addEventListener(this, UIEvent::CLICK_EVENT);
    resetSize();
    if(icons.size() == 1) {
        selectIndex(0);
    }
}

void UIIconSelector::selectIndex(unsigned int index) {
    selectedIndex = index;
    selectorRect->visible = true;
    selectorRect->setPosition(paddingX + (index * selectorSize), paddingY);
    dispatchEvent(new UIEvent(), UIEvent::SELECT_EVENT);
}

unsigned int UIIconSelector::getSelectedIndex() {
    return selectedIndex;
}

void UIIconSelector::handleEvent(Event *event){
    for(int i=0; i < icons.size(); i++) {
        if(icons[i] == event->getDispatcher()) {
            selectIndex(i);
            return;
        }
    }
}

void UIIconSelector::resetSize() {
    for(int i=0; i < icons.size(); i++) {
        icons[i]->setPosition(paddingX+(selectorSize*i), paddingY);
    }
    
    Number innerSize = icons.size() * selectorSize;
    setWidth((paddingX*2)+innerSize);
    setHeight((paddingY*2)+selectorSize);
    
    bgRect->resizeBox(getWidth(), getHeight());
}

UIIconSelector::~UIIconSelector() {
	if(!ownsChildren) {
        for(int i=0; i < icons.size(); i++) {
            delete icons[i];
        }
        delete bgRect;
        delete selectorRect;
    }
}