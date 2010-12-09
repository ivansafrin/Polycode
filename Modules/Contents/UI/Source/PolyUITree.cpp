/*
 *  PolyUITree.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUITree.h"

using namespace Polycode;

UITree::UITree(String icon, String text, float treeWidth, float treeOffset) : ScreenEntity() {
		
	
	Config *conf = CoreServices::getInstance()->getConfig();
	
	handleRotation = 0;
	this->treeWidth = treeWidth;
	this->treeOffset = treeOffset;
	fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	userData = NULL;
	
	cellPadding = conf->getNumericValue("Polycode", "uiTreeCellPadding");
	cellHeight = conf->getNumericValue("Polycode", "uiTreeCellHeight");
	this->size = conf->getNumericValue("Polycode", "uiDefaultFontSize");
	this->arrowIcon = conf->getStringValue("Polycode", "uiTreeArrowIconImage");	
	textLabel = new ScreenLabel(fontName,
								text,
								size,
								Label::ANTIALIAS_FULL);

/*	
	float st = conf->getNumericValue("Polycode", "uiTreeCellSkinT");
	float sr = conf->getNumericValue("Polycode", "uiTreeCellSkinR");
	float sb = conf->getNumericValue("Polycode", "uiTreeCellSkinB");
	float sl = conf->getNumericValue("Polycode", "uiTreeCellSkinL");	
	
	float padding = conf->getNumericValue("Polycode", "uiTreeCellSkinPadding");	
	
	bgBox = new UIBox(conf->getStringValue("Polycode", "uiTreeCellSkin"),
						  st,sr,sb,sl,
						  treeWidth+(padding*2), cellHeight+(padding*2));	
	*/
	bgBox = new ScreenShape(ScreenShape::SHAPE_RECT, treeWidth, cellHeight);	
	bgBox->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bgBox->setPosition(-treeOffset,0);	
	bgBox->setColor(1, 1, 1, 0);
	addChild(bgBox);
	
	
	float st = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinT");
	float sr = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinR");
	float sb = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinB");
	float sl = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinL");
	
	float padding = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinPadding");	
	
	selection = new UIBox(conf->getStringValue("Polycode", "uiTreeCellSelectorSkin"),
						  st,sr,sb,sl,
						  treeWidth+(padding*2), cellHeight+(padding*2));
	
	selection->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	selection->setPosition(-treeOffset-padding,-padding);
	selection->visible = false;
	addChild(selection);
	arrowIconImage = new ScreenImage(arrowIcon.c_str());
	arrowIconImage->setPosition(cellPadding,(cellHeight-arrowIconImage->getHeight())/2.0f);
	addChild(arrowIconImage);
	iconImage = new ScreenImage(icon.c_str());
	addChild(iconImage);
	iconImage->setPosition(arrowIconImage->getWidth()+(cellPadding*2),(cellHeight-iconImage->getHeight())/2.0f);

	addChild(textLabel);	
	textLabel->setPosition(arrowIconImage->getWidth()+iconImage->getWidth()+(cellPadding*3),(int)((cellHeight-(textLabel->getHeight()-6))/2.0f));
	collapsed = false;
	treeHeight = 0;
	toggleCollapsed();	
	selected = false;
	
	parent = NULL;
	selectedNode = NULL;
	arrowIconImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	bgBox->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);	
	
	setPositionMode(ScreenEntity::POSITION_CENTER);
	
	refreshTree();
}

void UITree::setSelected() {
	selected = true;
	refreshTree();
	if(parent == NULL) {
		selectedNode = this;
		clearSelection(selectedNode);
	}
	dispatchEvent(new UITreeEvent(this), UITreeEvent::SELECTED_EVENT);	
}

void UITree::handleEvent(Event *event) {
	if(event->getDispatcher() == arrowIconImage) {
		toggleCollapsed();
	} else if(event->getDispatcher() == bgBox) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				setSelected();
			break;
			case InputEvent::EVENT_DOUBLECLICK:
				dispatchEvent(new UITreeEvent(this), UITreeEvent::EXECUTED_EVENT);				
			break;
			default:				
			break;
		}
	} else {
		UITreeEvent *uiTreeEvent = (UITreeEvent*)event;
		bool targetIsChild = false;
		for(int i=0; i < treeChildren.size(); i++) {
			if(event->getDispatcher() == treeChildren[i])
				targetIsChild = true;
		}
		if(targetIsChild) {
		switch(event->getEventCode()) {
			case UITreeEvent::SELECTED_EVENT:
				if(parent == NULL) {
					selectedNode = uiTreeEvent->selection;
					if(selectedNode)
						clearSelection(selectedNode);
					dispatchEvent(new UITreeEvent(uiTreeEvent->selection), UITreeEvent::SELECTED_EVENT);					
				} else {
					dispatchEvent(new UITreeEvent(uiTreeEvent->selection), UITreeEvent::SELECTED_EVENT);
				}
			break;
			case UITreeEvent::EXECUTED_EVENT:
					dispatchEvent(new UITreeEvent(uiTreeEvent->selection), UITreeEvent::EXECUTED_EVENT);
			break;
			case UITreeEvent::NEED_REFRESH_EVENT:
				refreshTree();
				dispatchEvent(new UITreeEvent(), UITreeEvent::NEED_REFRESH_EVENT);
			break;
		}
		}
	}
}

void UITree::setIcon(String iconFile) {
	Texture *texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(iconFile);
	iconImage->setTexture(texture);
}

UITree *UITree::getSelectedNode() {
	return selectedNode;
}

bool UITree::isCollapsed() {
	return collapsed;
}

void UITree::clearSelection(UITree *selectedNode) {
	if(!selectedNode)
		return;
//	Logger::log("Selected node: %d\n", selectedNode);
	if(this != selectedNode) {
		selected = false;
		refreshTree();
	}
	
	for(int i=0; i < treeChildren.size(); i++) {
		treeChildren[i]->clearSelection(selectedNode);
	}
}

void UITree::refreshTree() {
	if(collapsed) {
		new Tween(&handleRotation, Tween::EASE_IN_QUAD, handleRotation, 0, 0.2f);
		for(int i=0; i < treeChildren.size(); i++) {
			treeChildren[i]->visible = false;
			treeChildren[i]->enabled = false;			
		}
		treeHeight = 0;
	} else {
		new Tween(&handleRotation, Tween::EASE_IN_QUAD, handleRotation, 90, 0.2f);
		int offset = cellHeight;
		for(int i=0; i < treeChildren.size(); i++) {
			treeChildren[i]->visible = true;
			treeChildren[i]->enabled = true;
			treeChildren[i]->setPosition(10,offset);
			offset += cellHeight + treeChildren[i]->getTreeHeight();
		}
		treeHeight = offset - cellHeight;
	}
	height = treeHeight + cellHeight;
	width = treeWidth;
	hitwidth = width;
	hitheight = height;
	
	selection->visible = selected;
}

float UITree::getTreeHeight() {
	return treeHeight;
}

void UITree::toggleCollapsed() {
	collapsed = !collapsed;
	refreshTree();
	dispatchEvent(new UITreeEvent(), UITreeEvent::NEED_REFRESH_EVENT);
}

UITree::~UITree() {
}

void UITree::Update() {
	arrowIconImage->setRotation(handleRotation);
	if(treeChildren.size() > 0)
		arrowIconImage->visible = true;
	else
		arrowIconImage->visible = false;
}

void UITree::setParent(UITree *parent) {
	this->parent = parent;
}

void *UITree::getUserData() {
	return userData;
}

void UITree::setUserData(void *data) {
	userData = data;
}

UITree *UITree::addTreeChild(String icon, String text, void *userData) {
	UITree *newTree = new UITree(icon, text, treeWidth, treeOffset+11);
	newTree->setUserData(userData);
	addChild(newTree);
	newTree->setParent(this);
	newTree->addEventListener(this, UITreeEvent::NEED_REFRESH_EVENT);
	newTree->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	newTree->addEventListener(this, UITreeEvent::EXECUTED_EVENT);
	treeChildren.push_back(newTree);
	refreshTree();
	return newTree;
}