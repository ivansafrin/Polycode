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


#include "PolyUITree.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include "PolyRenderer.h"

using namespace Polycode;

UITree::UITree(String icon, String text, Number treeWidth, Number treeOffset) : UIElement() {
		
	processInputEvents = true;
	willDrag = false;
	isDragging = false;
	
	labelText = text;
	Config *conf = CoreServices::getInstance()->getConfig();
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
	
	handleRotation = 0;
	this->treeWidth = treeWidth;
	this->treeOffset = treeOffset;
	fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	userData = NULL;
	
	cellPadding = conf->getNumericValue("Polycode", "uiTreeCellPadding");
	cellHeight = conf->getNumericValue("Polycode", "uiTreeCellHeight");
	this->size = conf->getNumericValue("Polycode", "uiDefaultFontSize");
	this->arrowIcon = conf->getStringValue("Polycode", "uiTreeArrowIconImage");	
	textLabel = new SceneLabel(
								text,
								size,
								fontName,
								Label::ANTIALIAS_FULL);
    textLabel->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	textLabel->color.setColorHexFromString(conf->getStringValue("Polycode", "uiTreeFontColor"));
    
	bgBox = new Entity();
    bgBox->setWidth(treeWidth);
    bgBox->setHeight(cellHeight);
	bgBox->setAnchorPoint(-1.0, -1.0, 0.0);
    bgBox->visible = false;
	addChild(bgBox);
	
	
	Number st = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinT");
	Number sr = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinR");
	Number sb = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinB");
	Number sl = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinL");
	
	Number padding = conf->getNumericValue("Polycode", "uiTreeCellSelectorSkinPadding");	
	this->padding = padding;
    
	selection = new UIBox(conf->getStringValue("Polycode", "uiTreeCellSelectorSkin"),
						  st,sr,sb,sl,
						  treeWidth+(padding*2), cellHeight+(padding*2));
	
	selection->setAnchorPoint(-1.0, -1.0, 0.0);
	selection->visible = false;
	addChild(selection);
	arrowIconImage = new UIImage(arrowIcon);
    arrowIconImage->Resize(arrowIconImage->getWidth() / uiScale, arrowIconImage->getHeight() / uiScale);
    arrowIconImage->setAnchorPoint(0.0, 0.0, 0.0);
    arrowIconImage->setPosition(treeOffset + (arrowIconImage->getWidth()/2.0) + cellPadding, (cellHeight) / 2.0);
    
	addChild(arrowIconImage);
	iconImage = new UIImage(icon);
    iconImage->Resize(iconImage->getWidth() / uiScale, iconImage->getHeight() / uiScale);
    
	addChild(iconImage);
    iconImage->setAnchorPoint(-1.0, -1.0, 0.0);
    iconImage->setPosition(treeOffset + arrowIconImage->getWidth() + cellPadding * 2.0, (cellHeight-iconImage->getHeight()) / 2.0);
    
    Number textOffsetX = conf->getNumericValue("Polycode", "uiTreeTextOffsetX");
    Number textOffsetY = conf->getNumericValue("Polycode", "uiTreeTextOffsetY");
    
	addChild(textLabel);
	textLabel->setPosition(treeOffset + arrowIconImage->getWidth()+iconImage->getWidth()+ textOffsetX + cellPadding * 3.0, textOffsetY);
    
	collapsed = false;
	treeHeight = 0;
	toggleCollapsed();	
	selected = false;
	
	parent = NULL;
	selectedNode = NULL;
	arrowIconImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	arrowIconImage->processInputEvents = true;	
	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);		
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	bgBox->addEventListener(this, InputEvent::EVENT_DOUBLECLICK);	
	bgBox->processInputEvents = true;
		
	setAnchorPoint(0.0, 0.0, 0.0);
	
	refreshTree();
}

void UITree::Resize(Number width) {
	treeWidth = width;
	selection->resizeBox(treeWidth+(padding*2), cellHeight+(padding*2));
	bgBox->setWidth(width);
    bgBox->setHeight(cellHeight);
	
	for(int i=0; i < treeChildren.size(); i++) {
		treeChildren[i]->Resize(width);
	}
}

void UITree::setLabelText(const String &text) {
	labelText = text;
	textLabel->setText(text);
}
			
String UITree::getLabelText() {
	return labelText;
}

void UITree::removeTreeChild(UITree *child) {
	for(int i=0; i < treeChildren.size(); i++) {
		if(treeChildren[i] == child) {			
			removeChild(child);
			child->removeEventListener(this, UITreeEvent::NEED_REFRESH_EVENT);
			child->removeEventListener(this, UITreeEvent::SELECTED_EVENT);
			child->removeEventListener(this, UITreeEvent::EXECUTED_EVENT);
			child->removeEventListener(this, UITreeEvent::DRAG_START_EVENT);			
			treeChildren.erase(treeChildren.begin()+i);
			delete child;
			refreshTree();			
			return;
		}
	}
}

void UITree::setSelected(bool byKey) {
	selectedByKey = byKey;
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
			case InputEvent::EVENT_MOUSEUP:
//				setSelected();
				willDrag = false;				
				isDragging = false;				
			break;
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:
				willDrag = false;	
				isDragging = false;			
			break;			
			case InputEvent::EVENT_MOUSEDOWN:	
				setSelected();			
//				willDrag = true;
//				mouseDownPosition = ((InputEvent*)event)->mousePosition;				
			break;			
			case InputEvent::EVENT_MOUSEMOVE:
				if(willDrag && !isDragging && ((InputEvent*)event)->mousePosition.distance(mouseDownPosition) > 5) {
					isDragging = true;
					dispatchEvent(new UITreeEvent(this), UITreeEvent::DRAG_START_EVENT);
				}
			break;						
			case InputEvent::EVENT_DOUBLECLICK:
				if (hasTreeChildren() && ((InputEvent*)event)->getMouseButton() == 0){
					toggleCollapsed();
				} else {
					dispatchEvent(new UITreeEvent(this), UITreeEvent::EXECUTED_EVENT);
				}
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
			case UITreeEvent::DRAG_START_EVENT:
					dispatchEvent(new UITreeEvent(uiTreeEvent->selection), UITreeEvent::DRAG_START_EVENT);
			break;			
			case UITreeEvent::NEED_REFRESH_EVENT:
				refreshTree();
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
		handleRotation = 0;
		for(int i=0; i < treeChildren.size(); i++) {
			treeChildren[i]->visible = false;
			treeChildren[i]->enabled = false;			
		}
		treeHeight = 0;
	} else {
		handleRotation = 90;
		int offset = cellHeight;
		for(int i=0; i < treeChildren.size(); i++) {
			treeChildren[i]->visible = true;
			treeChildren[i]->enabled = true;
			treeChildren[i]->setPosition(0.0,offset);
			offset += cellHeight + treeChildren[i]->getTreeHeight();
		}
		treeHeight = offset - cellHeight;
	}
	setHeight(treeHeight + cellHeight);
	setWidth(treeWidth);
	
	selection->visible = selected;
	dispatchEvent(new UITreeEvent(), UITreeEvent::NEED_REFRESH_EVENT);	
}

Number UITree::getTreeHeight() {
	return treeHeight;
}

void UITree::toggleCollapsed() {
	collapsed = !collapsed;
	refreshTree();
	dispatchEvent(new UITreeEvent(), UITreeEvent::NEED_REFRESH_EVENT);
}

UITree::~UITree() {
	clearTree();
	
	if(!ownsChildren) {
		delete textLabel;
		delete bgBox;
		delete selection;
		delete arrowIconImage;
		delete iconImage;
	}
}

void UITree::clearTree() {
	for(int i=0; i < treeChildren.size(); i++) {
		UITree *child = treeChildren[i];
		removeChild(child);
		child->removeEventListener(this, UITreeEvent::NEED_REFRESH_EVENT);
		child->removeEventListener(this, UITreeEvent::SELECTED_EVENT);
		child->removeEventListener(this, UITreeEvent::EXECUTED_EVENT);	
		delete child;
	}
	treeChildren.clear();
    dispatchEvent(new UITreeEvent(), UITreeEvent::NEED_REFRESH_EVENT);
}

void UITree::Update() {
	arrowIconImage->setRoll(-handleRotation);
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
	newTree->addEventListener(this, UITreeEvent::DRAG_START_EVENT);	
	treeChildren.push_back(newTree);
	refreshTree();
	return newTree;
}

UITree *UITree::getParent() {
	return parent;
}

UITree *UITree::getPrevSibling() {
	UITree *sibling = NULL;
	if (!parent)
		return sibling;
	for (int i=0; i < parent->getNumTreeChildren(); i++) {
		if (i > 0 && parent->getTreeChild(i) == this)
			sibling = parent->getTreeChild(i-1);
	}
	return sibling;
}

UITree *UITree::getNextSibling() {
	UITree *sibling = NULL;
	if (!parent)
		return sibling;
	for (int i=0; i < parent->getNumTreeChildren(); i++) {
		if (parent->getTreeChild(i) == this && i < parent->getNumTreeChildren()-1)
			sibling = parent->getTreeChild(i+1);
	}
	return sibling;
}