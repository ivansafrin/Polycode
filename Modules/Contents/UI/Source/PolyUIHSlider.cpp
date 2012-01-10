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


#include "PolyUIHSlider.h"

using namespace Polycode;

UIHSlider::UIHSlider(Number start, Number end, Number width) {
	bgRect = new ScreenShape(ScreenShape::SHAPE_RECT, width,8,0,0);
	bgRect->setPosition(0,6);
	bgRect->setColor(0.11f, 0.11f, 0.11f, 1.0f);
//	bgRect->strokeEnabled = true;
//	bgRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.1f);
	addChild(bgRect);
	
	sliderWidth = width-10;
	
	sliderValue = start;
	startValue = start;
	endValue = end;
	
	shadowRect = new ScreenShape(ScreenShape::SHAPE_RECT,10,18,0,0);
	shadowRect->setColor(0.0f, 0.0f, 0.0f, 0.2f);
	shadowRect->setPosition(2, 3);
	addChild(shadowRect);
	
	gripRect = new ScreenShape(ScreenShape::SHAPE_RECT, 10,18,0,0);
	gripRect->setColor(0.13f, 0.13f, 0.13f, 1.0f);
	gripRect->strokeEnabled = true;
	gripRect->lineSmooth = false;
	gripRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.1f);
	addChild(gripRect);

	gripRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	gripRect->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	gripRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	gripRect->setDragLimits(Rectangle(0,0,width-10,0));
	shadowRect->setDragLimits(Rectangle(2,3,width-10,0));
	
	gripPos = 0;
}

UIHSlider::~UIHSlider() {

}

ScreenShape *UIHSlider::getBgRect() {
	return bgRect;
}

void UIHSlider::setSliderValue(Number val) {
	if(val >= startValue && val <= endValue) {
		gripRect->setPositionX(sliderWidth * ((val-startValue)/(endValue-startValue)));
		shadowRect->setPositionX(gripRect->getPosition().x);
	}
}

Number UIHSlider::getSliderValue() {
	return sliderValue;
}
			
void UIHSlider::handleEvent(Event *event) {
	if(event->getDispatcher() == gripRect) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				gripRect->startDrag(inputEvent->mousePosition.x-gripRect->getPosition().x,inputEvent->mousePosition.y-gripRect->getPosition().y);
				shadowRect->startDrag(inputEvent->mousePosition.x-2-gripRect->getPosition().x,inputEvent->mousePosition.y-3-gripRect->getPosition().y);		
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:
				gripRect->stopDrag();
				shadowRect->stopDrag();
			break;
		}	
	}
}


void UIHSlider::Update() {
	if(gripRect->getPosition().x != gripPos) {
		gripPos = gripRect->getPosition().x;
		sliderValue = startValue+((endValue - startValue) * (gripPos/sliderWidth));
		dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
	}
}
