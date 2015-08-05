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


#include "PolyUIHSizer.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyUIEvent.h"

using namespace Polycode;

UIHSizer::UIHSizer(Number width, Number height, Number mainWidth, bool leftSizer) : UIElement() {

	minimumSize = 100;
	proportionalResize = false;

	setWidth(width);
	setHeight(height);
	this->leftSizer = leftSizer;
	this->mainWidth = mainWidth;
	
	separatorBgShape = new UIRect(1,height);
	separatorBgShape->setAnchorPoint(-1.0, -1.0, 0.0);
	separatorBgShape->setColor(0.0, 0.0, 0.0, 1.0);	
	addChild(separatorBgShape);
	

	childElements = new Entity();
	childElements->processInputEvents = true;
	addChild(childElements);
	
	firstElement = NULL;
	secondElement = NULL;
	
	separatorHitShape = new UIRect(8,height);
	separatorHitShape->setAnchorPoint(-1.0, -1.0, 0.0);
	separatorHitShape->setColor(1.0, 0.0, 0.0, 0.5);	
	separatorHitShape->blockMouseInput = true;	
	addChild(separatorHitShape);
	
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

UIHSizer::~UIHSizer() {
	coreInput->removeAllHandlersForListener(this);

    childElements->ownsChildren = false;
	if(!ownsChildren) {
		delete childElements;	
		delete separatorBgShape;
		delete separatorHitShape;
	}
}

void UIHSizer::handleEvent(Event *event) {
	if(event->getDispatcher() == separatorHitShape) {
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				resizing = true;
				baseMainWidth = mainWidth;
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:	
			{
				resizing = false;			
			}
			break;
			case InputEvent::EVENT_MOUSEMOVE:			
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_RESIZE_LEFT_RIGHT);
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
					if(leftSizer) {
						setMainWidthWithMinimum(baseMainWidth + (inputEvent->mousePosition.x-baseMouseX));
					} else {
						setMainWidthWithMinimum(baseMainWidth - (inputEvent->mousePosition.x-baseMouseX));
					}
				} else {
					baseMouseX = inputEvent->mousePosition.x;				
				}
			break;		
		}		
	}
}

void UIHSizer::setProportionalResize(bool val) {
	proportionalResize = val;
}

void UIHSizer::Resize(Number width, Number height) {

	if(proportionalResize) {
		mainWidth = mainWidth * (width/getWidth());
	}

	setWidth(width);
	setHeight(height);
	matrixDirty = true;
	updateSizer();
	UIElement::Resize(width, height);	
}

Number UIHSizer::getMainWidth() {
	return mainWidth;
}

void UIHSizer::setMainWidthWithMinimum(Number newWidth) {
	if(newWidth < minimumSize) {
		newWidth = minimumSize;
	}
	if(newWidth > getWidth()-minimumSize) {
		newWidth = getWidth()-minimumSize;
	}
	setMainWidth(newWidth);
}

void UIHSizer::setMainWidth(Number width) {
	mainWidth = width;
	updateSizer();
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}

void UIHSizer::setMinimumSize(Number minimumSize) {
	this->minimumSize = minimumSize;
}
			
void UIHSizer::addLeftChild(UIElement *element) {
	childElements->addChild(element);	
	firstElement = element;
	updateSizer();
}

void UIHSizer::addRightChild(UIElement *element) {
	childElements->addChild(element);
	secondElement = element;	
	updateSizer();
}

void UIHSizer::removeLeftChild() {
	if(firstElement) {
		childElements->removeChild(firstElement);
		firstElement = NULL;
	}
}

void UIHSizer::removeRightChild() {
	if(secondElement) {
		childElements->removeChild(secondElement);
		secondElement = NULL;
	}
}

UIElement *UIHSizer::getLeftChild() {
	return firstElement;
}

UIElement *UIHSizer::getRightChild() {
	return secondElement;
}

void UIHSizer::updateSizer() {

	if(leftSizer) {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(mainWidth, getHeight());
		}	
		if(secondElement) {
			secondElement->setPosition(mainWidth+1,0);
			secondElement->Resize(getWidth()-mainWidth-1, getHeight());	
		}

		separatorBgShape->Resize(1, getHeight());
		separatorBgShape->setPosition(mainWidth,0);
		separatorHitShape->Resize(8, getHeight());
		separatorHitShape->setPosition(mainWidth-4,0);
		
	} else {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(getWidth()-mainWidth, getHeight());
		}	
		if(secondElement) {
			secondElement->setPosition(getWidth()-mainWidth+1,0);
			secondElement->Resize(mainWidth-1, getHeight());	
		}

		separatorBgShape->Resize(1, getHeight());
		separatorBgShape->setPosition(getWidth()-mainWidth,0);
		separatorHitShape->Resize(8, getHeight());
		separatorHitShape->setPosition(getWidth()-mainWidth-4,0);
	
	}
}