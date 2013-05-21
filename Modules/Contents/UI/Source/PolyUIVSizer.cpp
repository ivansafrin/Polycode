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

using namespace Polycode;

UIVSizer::UIVSizer(Number width, Number height, Number mainHeight, bool topSizer) : UIElement() {

	this->width = width;
	this->height = height;
	this->topSizer = topSizer;
	this->mainHeight = mainHeight;
	
	separatorBgShape = new ScreenShape(ScreenShape::SHAPE_RECT, width,1);
	separatorBgShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	separatorBgShape->setColor(0.0, 0.0, 0.0, 1.0);	
	addChild(separatorBgShape);

	childElements = new ScreenEntity();
	childElements->processInputEvents = true;
	addChild(childElements);
	
	firstElement = NULL;
	secondElement = NULL;
	
	separatorHitShape = new ScreenShape(ScreenShape::SHAPE_RECT, width,8);
	separatorHitShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
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
	
	if (ownsChildren)
		childElements->ownsChildren = true;
		
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
						setMainHeight(baseMainHeight + (inputEvent->mousePosition.y-baseMouseY));
					} else {
						setMainHeight(baseMainHeight - (inputEvent->mousePosition.y-baseMouseY));		
					}
				} else {
					baseMouseY = inputEvent->mousePosition.y;
				}
			break;		
		}		
	}
}

void UIVSizer::Resize(Number width, Number height) {
	this->width = width;
	this->height = height;
	matrixDirty = true;
	updateSizer();
}

Number UIVSizer::getMainHeight() {
	return mainHeight;
}

void UIVSizer::setMainHeight(Number height) {
	mainHeight = height;
	updateSizer();
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

void UIVSizer::updateSizer() {

	if(topSizer) {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(width, mainHeight);
		}
	
		if(secondElement) {
			secondElement->setPosition(0,mainHeight+1);
			secondElement->Resize(width, height-mainHeight-1);				
		}

		separatorBgShape->setShapeSize(width, 1);
		separatorBgShape->setPosition(0,mainHeight);
		separatorHitShape->setShapeSize(width, 8);
		separatorHitShape->setPosition(0, mainHeight-4);
		
	} else {

		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(width, height-mainHeight);
		}
	
		if(secondElement) {
			secondElement->setPosition(0,height-mainHeight+1);
			secondElement->Resize(width, mainHeight-1);	
		}

		separatorBgShape->setShapeSize(width, 1);
		separatorBgShape->setPosition(0,height-mainHeight);
		separatorHitShape->setShapeSize(width, 8);
		separatorHitShape->setPosition(0, height-mainHeight-4);

	}	

}