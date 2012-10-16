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

using namespace Polycode;

UIHSizer::UIHSizer(Number width, Number height, Number mainWidth, bool leftSizer) : UIElement() {

	this->width = width;
	this->height = height;
	this->leftSizer = leftSizer;
	this->mainWidth = mainWidth;
	
	separatorBgShape = new ScreenShape(ScreenShape::SHAPE_RECT, 1,height);
	separatorBgShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	separatorBgShape->setColor(0.0, 0.0, 0.0, 1.0);	
	addChild(separatorBgShape);

	childElements = new ScreenEntity();
	addChild(childElements);
	
	firstElement = NULL;
	secondElement = NULL;
	
	separatorHitShape = new ScreenShape(ScreenShape::SHAPE_RECT, 6,height);
	separatorHitShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	separatorHitShape->setColor(1.0, 0.0, 0.0, 0.5);	
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

}

void UIHSizer::handleEvent(Event *event) {
	if(event->getDispatcher() == separatorHitShape) {
		InputEvent *inputEvent = (InputEvent*)event;
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
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_RESIZE_LEFT_RIGHT);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_ARROW);
			break;							
		}
	}
	
	if(event->getDispatcher() == coreInput) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				if(resizing == true) {
					if(leftSizer) {
						setMainWidth(baseMainWidth + (inputEvent->mousePosition.x-baseMouseX));
					} else {
						setMainWidth(baseMainWidth - (inputEvent->mousePosition.x-baseMouseX));
					}
				} else {
					baseMouseX = inputEvent->mousePosition.x;				
				}
			break;		
		}		
	}
}

void UIHSizer::Resize(Number width, Number height) {
	this->width = width;
	this->height = height;
	matrixDirty = true;
	updateSizer();
}

void UIHSizer::setMainWidth(Number width) {
	mainWidth = width;
	updateSizer();
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

void UIHSizer::updateSizer() {

	if(leftSizer) {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(mainWidth, height);
		}	
		if(secondElement) {
			secondElement->setPosition(mainWidth+1,0);
			secondElement->Resize(width-mainWidth-1, height);	
		}

		separatorBgShape->setShapeSize(1, height);
		separatorBgShape->setPosition(mainWidth,0);
		separatorHitShape->setShapeSize(6, height);
		separatorHitShape->setPosition(mainWidth-3,0);
		
	} else {
	
		if(firstElement) {
			firstElement->setPosition(0,0);
			firstElement->Resize(width-mainWidth, height);
		}	
		if(secondElement) {
			secondElement->setPosition(width-mainWidth+1,0);
			secondElement->Resize(mainWidth-1, height);	
		}

		separatorBgShape->setShapeSize(1, height);
		separatorBgShape->setPosition(width-mainWidth,0);
		separatorHitShape->setShapeSize(6, height);
		separatorHitShape->setPosition(width-mainWidth-3,0);
	
	}
}