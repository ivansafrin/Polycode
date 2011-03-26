/*
 *  PolyUITreeContainer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/18/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyUITreeContainer.h"

using namespace Polycode;

UITreeContainer::UITreeContainer(String icon, String text, float treeWidth, float treeHeight) : ScreenEntity() {
	
	Config *conf = CoreServices::getInstance()->getConfig();
	
	float st = conf->getNumericValue("Polycode", "uiTreeContainerSkinT");
	float sr = conf->getNumericValue("Polycode", "uiTreeContainerSkinR");
	float sb = conf->getNumericValue("Polycode", "uiTreeContainerSkinB");
	float sl = conf->getNumericValue("Polycode", "uiTreeContainerSkinL");	
	float padding = conf->getNumericValue("Polycode", "uiTreeContainerSkinPadding");	
	
//	float scrollBarOffset = conf->getNumericValue("Polycode", "uiTreeContainerScrollBarOffset");	
	
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
	hitwidth = width;
	hitheight = height;
}

void UITreeContainer::Resize(int x, int y) {
	mainContainer->Resize(x,y);
	bgBox->resizeBox(x, y);
	mainContainer->setPositionY(0);

//	width = x;
//	height = y;
	hitwidth = x;
	hitheight = y;

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
