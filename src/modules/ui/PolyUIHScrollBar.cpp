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


#include "PolyUIHScrollBar.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"

using namespace Polycode;

UIHScrollBar::UIHScrollBar(Number width, Number height, Number initialRatio) : UIElement() {
	
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
	bgBox->processInputEvents = true;
	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);		
	handleBox->processInputEvents = true;
	handleBox->blockMouseInput = true;
	
	dragRectWidth = width-(padding*2)-scrollHandleWidth;
	handleBox->setDragLimits(Rectangle(padding,padding,dragRectWidth, height-(padding*2)-(height-(padding*2))));
	
	lastPositionX = handleBox->getPosition().x;
	
	setHeight(height);
	setWidth(width);	
}

void UIHScrollBar::Resize(int newWidth) {
	bgBox->resizeBox(newWidth, getHeight());
	setWidth(newWidth);
	dragRectWidth = getWidth()-(padding*2)-scrollHandleWidth;	
	handleBox->setDragLimits(Rectangle(padding,padding,dragRectWidth, getHeight()-(padding*2)-(getHeight()-(padding*2))));
}

void UIHScrollBar::Update() {
	if(lastPositionX != handleBox->getPosition().x) {
		lastPositionX = handleBox->getPosition().x;
		scrollValue = (lastPositionX-padding)/dragRectWidth;

		if(scrollValue < 0){
			scrollValue = 0;
			handleBox->setPositionX((scrollValue * dragRectWidth) + padding);	
		}
		
		if(scrollValue > 1) {
			scrollValue = 1;
			handleBox->setPositionX((scrollValue * dragRectWidth) + padding);	
		}
		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void UIHScrollBar::setHandleRatio(Number newRatio) {
	scrollHandleWidth = getWidth()*newRatio;	
	
	if(scrollHandleWidth < minHandleSize)
		scrollHandleWidth = minHandleSize;
	
	dragRectWidth = getWidth()-(padding*2)-scrollHandleWidth;	
	
	handleBox->resizeBox(scrollHandleWidth, handleBox->getHeight());
	handleBox->setDragLimits(Rectangle(padding,padding,dragRectWidth, getHeight()-(padding*2)-(getHeight()-(padding*2))));	
	
	if(enabled && handleBox->getPosition().x > dragRectWidth) {
		handleBox->setPositionX(dragRectWidth);
	}
	
}

Number UIHScrollBar::getScrollValue() {
	return scrollValue;
}

void UIHScrollBar::scrollTo(Number scrollValue) {
	handleBox->setPositionX((scrollValue * dragRectWidth) + padding);	
}

void UIHScrollBar::Scroll(Number amount) {
	handleBox->setPositionX(((scrollValue+amount) * dragRectWidth) + padding);	
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
				handleBox->startDrag(inputEvent->mousePosition.x,inputEvent->mousePosition.y);
				break;		
		}
	}
}


UIHScrollBar::~UIHScrollBar() {
	if(!ownsChildren) {
		delete bgBox;
		delete handleBox;
	}
}
