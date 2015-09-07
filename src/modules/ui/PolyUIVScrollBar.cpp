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


#include "PolyUIVScrollBar.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"

using namespace Polycode;

UIVScrollBar::UIVScrollBar(Number width, Number height, Number initialRatio) : UIElement() {

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
	
	bgBox->processInputEvents = true;
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	bgBox->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
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
		
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	handleBox->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	handleBox->processInputEvents = true;
	handleBox->blockMouseInput = true;
	
	
	dragRectHeight = height-(padding*2)-scrollHandleHeight;
	handleBox->setDragLimits(Rectangle(padding,padding,width-(padding*2)-(width-(padding*2)), dragRectHeight));
	
	lastPositionY = handleBox->getPosition().y;
	
	setHeight(height);
	setWidth(width);	
	
	tickSize = 0.1;
}

void UIVScrollBar::Resize(int newHeight) {
	bgBox->resizeBox(getWidth(), newHeight);
	setHeight(newHeight);
	dragRectHeight = getHeight()-(padding*2)-scrollHandleHeight;	
	handleBox->setDragLimits(Rectangle(padding,padding,getWidth()-(padding*2)-(getWidth()-(padding*2)), dragRectHeight));	
}

void UIVScrollBar::Update() {
	
	if(lastPositionY != handleBox->getPosition().y) {
		lastPositionY = handleBox->getPosition().y;
		scrollValue = (lastPositionY-padding)/dragRectHeight;
		if(scrollValue < 0){
			scrollValue = 0;
			handleBox->setPositionY((scrollValue * dragRectHeight) + padding);							
		}
		
		if(scrollValue > 1) {
			scrollValue = 1;
			handleBox->setPositionY((scrollValue * dragRectHeight) + padding);				
		}
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
}

void UIVScrollBar::scrollTo(Number scrollValue) {
	handleBox->setPositionY((scrollValue * dragRectHeight) + padding);	
}

void UIVScrollBar::Scroll(Number amount) {
	Number newValue = scrollValue+amount;
	if(newValue > 1.0)
		newValue = 1.0;
	if(newValue < 0.0)
		newValue = 0.0;		
	handleBox->setPositionY(((newValue) * dragRectHeight) + padding);	
}

void UIVScrollBar::setHandleRatio(Number newRatio) {
    
	scrollHandleHeight = getHeight()*newRatio;	
	
	if(scrollHandleHeight < minHandleSize)
		scrollHandleHeight = minHandleSize;

	dragRectHeight = getHeight()-(padding*2)-scrollHandleHeight;	
	handleBox->resizeBox(handleBox->getWidth(), scrollHandleHeight);
	handleBox->setDragLimits(Rectangle(padding,padding,getWidth()-(padding*2)-(getWidth()-(padding*2)), dragRectHeight));	
	
	if(enabled && handleBox->getPosition().y > dragRectHeight) {
		handleBox->setPositionY(dragRectHeight);
	}
	
}

void UIVScrollBar::onMouseWheelUp(Number x, Number y) {
	scrollUpOneTick();
}

void UIVScrollBar::onMouseWheelDown(Number x, Number y) {
	scrollDownOneTick();
}

void UIVScrollBar::setTickSize(Number newTickSize) {
	tickSize = newTickSize;
}

void UIVScrollBar::scrollUpOneTick() {
	Scroll(-tickSize);
}

void UIVScrollBar::scrollDownOneTick() {
	Scroll(tickSize);
}


Number UIVScrollBar::getScrollValue() {
	return scrollValue;
}

void UIVScrollBar::handleEvent(Event *event) {
	if(event->getDispatcher() == bgBox) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				if(inputEvent->mousePosition.y < handleBox->getPosition().y)  {
					Number newPos = handleBox->getPosition().y - scrollHandleHeight/2;
					if(newPos < padding)
						newPos = padding;
					handleBox->setPositionY(newPos);
				} else {
					Number newPos = handleBox->getPosition().y + scrollHandleHeight/2;
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
			case InputEvent::EVENT_MOUSEOVER:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
			break;		
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
	

UIVScrollBar::~UIVScrollBar() {
    if(!ownsChildren) {
        delete bgBox;
        delete handleBox;
    }
}
