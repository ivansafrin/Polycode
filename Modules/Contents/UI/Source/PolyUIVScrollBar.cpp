/*
 *  PolyUIVScrollBar.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/25/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */


#include "PolyUIVScrollBar.h"

using namespace Polycode;

UIVScrollBar::UIVScrollBar(float width, float height, float initialRatio) : ScreenEntity() {

	scrollValue = 0;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	minHandleSize = conf->getNumericValue("Polycode", "uiScrollHandleMinSize");
	
	float st = conf->getNumericValue("Polycode", "uiScrollBgSkinT");
	float sr = conf->getNumericValue("Polycode", "uiScrollBgSkinR");
	float sb = conf->getNumericValue("Polycode", "uiScrollBgSkinB");
	float sl = conf->getNumericValue("Polycode", "uiScrollBgSkinL");	
	padding = conf->getNumericValue("Polycode", "uiScrollBgSkinPadding");		
		
	bgBox = new UIBox(conf->getStringValue("Polycode", "uiScrollBgSkin"),
					  st,sr,sb,sl,
					  width, height);
	
	addChild(bgBox);
	
	st = conf->getNumericValue("Polycode", "uiScrollHandleSkinT");
	sr = conf->getNumericValue("Polycode", "uiScrollHandleSkinR");
	sb = conf->getNumericValue("Polycode", "uiScrollHandleSkinB");
	sl = conf->getNumericValue("Polycode", "uiScrollHandleSkinL");	
	
	if(initialRatio > 1)
		initialRatio = 1;
	
	scrollHandleHeight = height*initialRatio;	
	
	if(scrollHandleHeight < minHandleSize)
		scrollHandleHeight = minHandleSize;
	
	handleBox = new UIBox(conf->getStringValue("Polycode", "uiScrollHandleSkin"),
					  st,sr,sb,sl,
					  width-(padding*2),scrollHandleHeight);
	handleBox->setPosition(padding, padding);	
	addChild(handleBox);
	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);			
	
	handleBox->blockMouseInput = true;
	
	dragRectHeight = height-(padding*2)-scrollHandleHeight;
	handleBox->setDragLimits(Rectangle(padding,padding,width-(padding*2)-(width-(padding*2)), dragRectHeight));
	
	lastPositionY = handleBox->getPosition()->y;
	
	this->height = height;
	this->width = width;	
	
	this->hitwidth = width;
	this->hitheight = height;	
}

void UIVScrollBar::Resize(int newHeight) {
	bgBox->resizeBox(width, newHeight);
	this->height = newHeight;
	this->hitheight = newHeight;
	dragRectHeight = height-(padding*2)-scrollHandleHeight;	
	handleBox->setDragLimits(Rectangle(padding,padding,width-(padding*2)-(width-(padding*2)), dragRectHeight));	
}

void UIVScrollBar::Update() {
	
	if(lastPositionY != handleBox->getPosition()->y) {
		lastPositionY = handleBox->getPosition()->y;
		scrollValue = (lastPositionY-padding)/dragRectHeight;
		if(scrollValue < 0) scrollValue = 0;
		if(scrollValue > 1) scrollValue = 1;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void UIVScrollBar::setHandleRatio(float newRatio) {
	scrollHandleHeight = height*newRatio;	
	
	if(scrollHandleHeight < minHandleSize)
		scrollHandleHeight = minHandleSize;

	dragRectHeight = height-(padding*2)-scrollHandleHeight;	
	handleBox->resizeBox(handleBox->getWidth(), scrollHandleHeight);
	handleBox->setDragLimits(Rectangle(padding,padding,width-(padding*2)-(width-(padding*2)), dragRectHeight));	
}

void UIVScrollBar::onMouseWheelUp(float x, float y) {
	scrollUpOneTick();
}

void UIVScrollBar::onMouseWheelDown(float x, float y) {
	scrollDownOneTick();
}

void UIVScrollBar::scrollUpOneTick() {
	float newPos = handleBox->getPosition()->y - 5;
	
	if(newPos < padding)
		newPos = padding;
	
	handleBox->setPositionY(newPos);	
}

void UIVScrollBar::scrollDownOneTick() {
	float newPos = handleBox->getPosition()->y + 5;	
	
	if(newPos > dragRectHeight)
		newPos = dragRectHeight;
	
	handleBox->setPositionY(newPos);	
}


float UIVScrollBar::getScrollValue() {
	return scrollValue;
}

void UIVScrollBar::handleEvent(Event *event) {
	if(event->getDispatcher() == bgBox) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(inputEvent->mousePosition.y < handleBox->getPosition()->y)  {
					float newPos = handleBox->getPosition()->y - scrollHandleHeight;
					if(newPos < padding)
						newPos = padding;
					handleBox->setPositionY(newPos);
				} else {
					float newPos = handleBox->getPosition()->y + scrollHandleHeight;
					if(newPos > dragRectHeight)
						newPos = dragRectHeight;
					handleBox->setPositionY(newPos);					
				}
			break;
		}
	}
	
	if(event->getDispatcher() == handleBox) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:				
				handleBox->stopDrag();
				break;
			case InputEvent::EVENT_MOUSEDOWN:
				handleBox->startDrag(inputEvent->mousePosition.x-handleBox->getPosition()->x,inputEvent->mousePosition.y-handleBox->getPosition()->y);
				break;		
		}
	}
}
	

UIVScrollBar::~UIVScrollBar() {
	
}
