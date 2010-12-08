/*
 *  PolyUIImageButton.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyUIImageButton.h"

using namespace Polycode;

UIImageButton::UIImageButton(string imageName) : ScreenEntity() {
	setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	
	buttonImage = new ScreenImage(imageName.c_str());
	addChild(buttonImage);
	
	buttonRect = new ScreenShape(ScreenShape::SHAPE_RECT, buttonImage->getWidth(),buttonImage->getHeight(),0,0);
	buttonRect->setColor(1,1,1,0);
	buttonRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(buttonRect);
	
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pressedDown = false;
	
	width = buttonRect->getWidth();
	height = buttonRect->getHeight();	
}

void UIImageButton::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEOVER:
				this->setColor(0.7,0.7,0.7,1);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				pressedDown = false;
				this->setColor(1,1,1,1);
			break;
			case InputEvent::EVENT_MOUSEUP:
				this->setColor(0.7,0.7,0.7,1);				
				if(pressedDown) {
					dispatchEvent(new UIEvent(), UIEvent::CLICK_EVENT);
				}
				pressedDown = false;				
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				pressedDown = true;
				this->setColor(0.5,0.5,0.5,1);				
			break;
		}
	}
}

UIImageButton::~UIImageButton() {

}
