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


#include "PolyUIVSizer.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyUIEvent.h"

using namespace Polycode;

UIVSizer::UIVSizer(Number width, Number height, Number mainHeight, bool topSizer) : UIElement() {

	minimumSize = 100;
	proportionalResize = false;

	setWidth(width);
	setHeight(height);
	this->topSizer = topSizer;
	this->mainHeight = mainHeight;
	
	separatorBgShape = new UIRect(width,1);
	separatorBgShape->setAnchorPoint(-1.0, -1.0, 0.0);
	separatorBgShape->setColor(0.0, 0.0, 0.0, 1.0);	
	addChild(separatorBgShape);

	childElements = new Entity();
	childElements->processInputEvents = true;
	addChild(childElements);
	
	firstElement = NULL;
	secondElement = NULL;
	
	separatorHitShape = new UIRect(width,8);
	separatorHitShape->setAnchorPoint(-1.0, -1.0, 0.0);
	separatorHitShape->setColor(1.0, 0.0, 0.0, 0.5);	
	addChild(separatorHitShape);
	separatorHitShape->blockMouseInput = true;
	
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEOVER);	
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEOUT);		
	separatorHitShape->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);			
	separatorHitShape->visible = false;
	
	coreInput = CoreServices::getInstance()->getCore()->getInput();
	
	coreInput->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);	
	
	separatorHitShape->processInputEvents = true;
	
	updateSizer();
	resizing = false;

}

UIVSizer::~UIVSizer() {
	coreInput->removeAllHandlersForListener(this);
			
    childElements->ownsChildren = false;
	if(!ownsChildren) {
		delete childElements;	
		delete separatorBgShape;
		delete separatorHitShape;
	}
}

void UIVSizer::handleEvent(Event *event) {
	if(event->getDispatcher() == separatorHitShape) {
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				resizing = true;
				baseMainHeight = mainHeight;
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:	
			{
				resizing = false;			
			}
			break;
			case InputEvent::EVENT_MOUSEMOVE:			
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_RESIZE_UP_DOWN);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
			break;							
		}
	}
	
	if(event->getDispatcher() == coreInput) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				if(resizing == true) {
					if(topSizer) {
						setMainHeightWithMinimum(baseMainHeight + (inputEvent->mousePosition.y-baseMouseY));
					} else {
						setMainHeightWithMinimum(baseMainHeight - (inputEvent->mousePosition.y-baseMouseY));		
					}
				} else {
					baseMouseY = inputEvent->mousePosition.y;
				}
			break;		
		}		
	}
}

void UIVSizer::setProportionalResize(bool val) {
	proportionalResize = val;
}

void UIVSizer::Resize(Number width, Number height) {

	if(proportionalResize) {
		mainHeight = mainHeight * (height/getHeight());
	}
	
	setWidth(width);
	setHeight(height);
	matrixDirty = true;
	updateSizer();
	UIElement::Resize(width, height);
}

Number UIVSizer::getMainHeight() {
	return mainHeight;
}

void UIVSizer::setMainHeightWithMinimum(Number newHeight) {
	if(newHeight < minimumSize) {
		newHeight = minimumSize;
	}	
	if(newHeight > getHeight()-minimumSize) {
		newHeight = getHeight()-minimumSize;
	}
	setMainHeight(newHeight);
}

void UIVSizer::setMinimumSize(Number minimumSize) {
	this->minimumSize = minimumSize;
}

void UIVSizer::setMainHeight(Number height) {
	mainHeight = height;
	updateSizer();
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
}
			
void UIVSizer::addTopChild(UIElement *element) {
	childElements->addChild(element);	
	firstElement = element;
	updateSizer();
}

void UIVSizer::addBottomChild(UIElement *element) {
	childElements->addChild(element);
	secondElement = element;	
	updateSizer();
}

void UIVSizer::removeTopChild() {
	if(firstElement) {
		childElements->removeChild(firstElement);
		firstElement = NULL;
	}
}

void UIVSizer::removeBottomChild() {
	if(secondElement) {
		childElements->removeChild(secondElement);
		secondElement = NULL;
	}
}

UIElement *UIVSizer::getTopChild() {
	return firstElement;
}

UIElement *UIVSizer::getBottomChild() {
	return secondElement;
}

void UIVSizer::updateSizer() {

	if(topSizer) {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(getWidth(), mainHeight);
		}
	
		if(secondElement) {
			secondElement->setPosition(0,mainHeight+1);
			secondElement->Resize(getWidth(), getHeight()-mainHeight-1);				
		}

		separatorBgShape->Resize(getWidth(), 1);
		separatorBgShape->setPosition(0,mainHeight);
		separatorHitShape->Resize(getWidth(), 8);
		separatorHitShape->setPosition(0, mainHeight-4);
		
	} else {

		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(getWidth(), getHeight()-mainHeight);
		}
	
		if(secondElement) {
			secondElement->setPosition(0,getHeight()-mainHeight+1);
			secondElement->Resize(getWidth(), mainHeight-1);	
		}

		separatorBgShape->Resize(getWidth(), 1);
		separatorBgShape->setPosition(0,getHeight()-mainHeight);
		separatorHitShape->Resize(getWidth(), 8);
		separatorHitShape->setPosition(0, getHeight()-mainHeight-4);

	}	

}