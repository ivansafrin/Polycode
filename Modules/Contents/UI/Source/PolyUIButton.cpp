/*
 *  PolyUIButton.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 8/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUIButton.h"

using namespace Polycode;

UIButton::UIButton(String text, float width, float height) : ScreenEntity() {

	Config *conf = CoreServices::getInstance()->getConfig();	
	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiButtonFontSize");	
	
	float st = conf->getNumericValue("Polycode", "uiButtonSkinT");
	float sr = conf->getNumericValue("Polycode", "uiButtonSkinR");
	float sb = conf->getNumericValue("Polycode", "uiButtonSkinB");
	float sl = conf->getNumericValue("Polycode", "uiButtonSkinL");
	
	
	buttonRect = new UIBox(conf->getStringValue("Polycode", "uiButtonSkin"),
						   st,sr,sb,sl,
						   width, height);	
	
	buttonFocusedRect= new UIBox(conf->getStringValue("Polycode", "uiButtonFocusedSkin"),
								 st,sr,sb,sl,
								 width, height);		
	
	addChild(buttonRect);
	addChild(buttonFocusedRect);
	
	buttonFocusedRect->visible = false;
	
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pressedDown = false;
	
	buttonLabel = new ScreenLabel(fontName, text, fontSize, Label::ANTIALIAS_FULL);
	addChild(buttonLabel);
	labelXPos = floor((width-buttonLabel->getWidth())/2.0f);
	labelYPos = floor((height-(buttonLabel->getHeight()-5))/2.0f);
	buttonLabel->setPosition(labelXPos,labelYPos);
	
	this->width = width;
	this->height = height;
	focusable = true;
	
}

void UIButton::Update() {
	if(hasFocus) {
		buttonFocusedRect->visible = true;
		buttonRect->visible = false;
	} else {
		buttonFocusedRect->visible = false;
		buttonRect->visible = true;
	}
}

UIButton::~UIButton() {

}
		
void UIButton::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEOVER:
			break;
			case InputEvent::EVENT_MOUSEOUT:
				buttonLabel->setPosition(labelXPos,labelYPos);
				buttonRect->setPosition(0,0);				
				pressedDown = false;
			break;
			case InputEvent::EVENT_MOUSEUP:
				buttonLabel->setPosition(labelXPos,labelYPos);
				buttonRect->setPosition(0,0);
				if(pressedDown) {
					dispatchEvent(new UIEvent(), UIEvent::CLICK_EVENT);
				}
				pressedDown = false;
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				pressedDown = true;
				if(parentEntity)
					((ScreenEntity*)parentEntity)->focusChild(this);
				buttonLabel->setPosition(labelXPos+1,labelYPos+1);
				buttonRect->setPosition(1,1);
			break;
		}
	}
}