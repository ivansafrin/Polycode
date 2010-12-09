/*
 *  PolyUICheckBox.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 8/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyUICheckBox.h"

using namespace Polycode;

UICheckBox::UICheckBox(Font *font, String checkImage, String caption, bool checked) {
	buttonImage = new ScreenImage(checkImage.c_str());
	buttonImage->setPosition(2, 3);
	this->checked = checked;
	buttonImage->visible = checked;
	
	captionLabel = new ScreenLabel("", caption, 11, Label::ANTIALIAS_FULL);
	addChild(captionLabel);
	captionLabel->setPosition(buttonImage->getWidth()+14,0);
	
	buttonRect = new ScreenShape(ScreenShape::SHAPE_RECT, buttonImage->getWidth()+5,buttonImage->getHeight()+5,0,0);
	buttonRect->setColor(0.1f, 0.1f, 0.1f, 1.0f);
	buttonRect->strokeEnabled = true;
	buttonRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.1f);
	addChild(buttonRect);
	addChild(buttonImage);
	
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	captionLabel->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
}

UICheckBox::~UICheckBox() {

}

bool UICheckBox::isChecked() {
	return checked;
}
		
void UICheckBox::changeCheck() {
	checked = !checked;
	buttonImage->visible = checked;
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}
		
void UICheckBox::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonRect || event->getDispatcher() == captionLabel) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				changeCheck();
			break;
		}
	}
}
