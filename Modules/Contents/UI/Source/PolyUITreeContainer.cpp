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

#include "PolyUITreeContainer.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"

using namespace Polycode;

UITreeContainer::UITreeContainer(String icon, String text, Number treeWidth, Number treeHeight) : UIElement() {
	
	Config *conf = CoreServices::getInstance()->getConfig();
	
	Number st = conf->getNumericValue("Polycode", "uiTreeContainerSkinT");
	Number sr = conf->getNumericValue("Polycode", "uiTreeContainerSkinR");
	Number sb = conf->getNumericValue("Polycode", "uiTreeContainerSkinB");
	Number sl = conf->getNumericValue("Polycode", "uiTreeContainerSkinL");	
	Number padding = conf->getNumericValue("Polycode", "uiTreeContainerSkinPadding");	
	
//	Number scrollBarOffset = conf->getNumericValue("Polycode", "uiTreeContainerScrollBarOffset");	
	
	bgBox = new UIBox(conf->getStringValue("Polycode", "uiTreeContainerSkin"),
						  st,sr,sb,sl,
						  treeWidth, treeHeight);
	
	addChild(bgBox);
	//bgBox->setPosition(-padding, -padding);
	
	scrollChild = new ScreenEntity();
	
	rootNode = new UITree(icon, text, treeWidth,0);		
	rootNode->addEventListener(this, UITreeEvent::NEED_REFRESH_EVENT);	
	scrollChild->addChild(rootNode);
	
	mainContainer = new UIScrollContainer(scrollChild, false, true, treeWidth-conf->getNumericValue("Polycode", "uiScrollDefaultSize"), treeHeight);
	addChild(mainContainer);
	
	width = treeWidth;
	height = treeHeight;
	setHitbox(width, height);
	
	Resize(width, height);
}

void UITreeContainer::Resize(Number width, Number height) {
	mainContainer->Resize(width,height);
	bgBox->resizeBox(width, height);
	mainContainer->setPositionY(0);


	rootNode->Resize(width);
//	width = x;
	//	height = y;
	setHitbox(width, height);
}

void UITreeContainer::handleEvent(Event *event) {
	if(event->getDispatcher() == rootNode) {
		if(event->getEventCode() == UITreeEvent::NEED_REFRESH_EVENT) {
			mainContainer->setContentSize(rootNode->getWidth(), rootNode->getHeight());
		}
	}
	
}

UITree *UITreeContainer::getRootNode() {
	return rootNode;
}

UITreeContainer::~UITreeContainer() {
	
}
