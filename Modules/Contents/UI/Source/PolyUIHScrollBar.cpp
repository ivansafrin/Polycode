/*
 *  PolyUIHScrollBar.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/26/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */


#include "PolyUIHScrollBar.h"

using namespace Polycode;

UIHScrollBar::UIHScrollBar(Number width, Number height, Number initialRatio) : ScreenEntity() {
	
	scrollValue = 0;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	minHandleSize = conf->getNumericValue("Polycode", "uiScrollHandleMinSize");
	
	Number st = conf->getNumericValue("Polycode", "uiScrollBgSkinT");
	Number sr = conf->getNumericValue("Polycode", "uiScrollBgSkinR");
	Number sb = conf->getNumericValue("Polycode", "uiScrollBgSkinB");
	Number sl = conf->getNumericValue("Polycode", "uiScrollBgSkinL");	
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
	
	scrollHandleWidth = width*initialRatio;	
	
	if(scrollHandleWidth < minHandleSize)
		scrollHandleWidth = minHandleSize;
	
	handleBox = new UIBox(conf->getStringValue("Polycode", "uiScrollHandleSkin"),
						  st,sr,sb,sl,
						  scrollHandleWidth,height-(padding*2));
	
	handleBox->setPosition(padding, padding);	
	addChild(handleBox);
	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);		
	
	handleBox->blockMouseInput = true;
	
	dragRectWidth = width-(padding*2)-scrollHandleWidth;
	handleBox->setDragLimits(Rectangle(padding,padding,dragRectWidth, height-(padding*2)-(height-(padding*2))));
	
	lastPositionX = handleBox->getPosition().x;
	
	this->height = height;
	this->width = width;	
}

void UIHScrollBar::Update() {
	if(lastPositionX != handleBox->getPosition().x) {
		lastPositionX = handleBox->getPosition().x;
		scrollValue = (lastPositionX-padding)/dragRectWidth;
		if(scrollValue < 0) scrollValue = 0;
		if(scrollValue > 1) scrollValue = 1;		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void UIHScrollBar::setHandleRatio(Number newRatio) {
	scrollHandleWidth = width*newRatio;	
	
	if(scrollHandleWidth < minHandleSize)
		scrollHandleWidth = minHandleSize;
	
	dragRectWidth = width-(padding*2)-scrollHandleWidth;	
	
	handleBox->resizeBox(scrollHandleWidth, handleBox->getHeight());
	handleBox->setDragLimits(Rectangle(padding,padding,dragRectWidth, height-(padding*2)-(height-(padding*2))));	
}

Number UIHScrollBar::getScrollValue() {
	return scrollValue;
}

void UIHScrollBar::handleEvent(Event *event) {
	if(event->getDispatcher() == bgBox) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(inputEvent->mousePosition.x < handleBox->getPosition().x)  {
					Number newPos = handleBox->getPosition().x - scrollHandleWidth;
					if(newPos < padding)
						newPos = padding;
					handleBox->setPositionX(newPos);
				} else {
					Number newPos = handleBox->getPosition().x + scrollHandleWidth;
					if(newPos > dragRectWidth)
						newPos = dragRectWidth;
					handleBox->setPositionX(newPos);					
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
				handleBox->startDrag(inputEvent->mousePosition.x-handleBox->getPosition().x,inputEvent->mousePosition.y-handleBox->getPosition().y);
				break;		
		}
	}
}


UIHScrollBar::~UIHScrollBar() {
	
}
