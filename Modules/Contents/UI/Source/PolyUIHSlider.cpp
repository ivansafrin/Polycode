/*
 *  PolyUIHSlider.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 8/7/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUIHSlider.h"

using namespace Polycode;

UIHSlider::UIHSlider(Font *font, float start, float end, float width) {
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

void UIHSlider::setSliderValue(float val) {
	if(val >= startValue && val <= endValue) {
		gripRect->getPosition().x = sliderWidth * ((val-startValue)/(endValue-startValue));
		shadowRect->getPosition().x = gripRect->getPosition().x;
	}
}

float UIHSlider::getSliderValue() {
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
