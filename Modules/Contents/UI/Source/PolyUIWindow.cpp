/*
 *  PolyUIWindow.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUIWindow.h"

using namespace Polycode;


UIWindow::UIWindow(String windowName, float width, float height) : ScreenEntity() {
	
	closeOnEscape = false;
	
	snapToPixels = true;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	String fontName = conf->getStringValue("Polycode", "uiWindowTitleFont");
	int fontSize = conf->getNumericValue("Polycode", "uiWindowTitleFontSize");	
	
	float st = conf->getNumericValue("Polycode", "uiWindowSkinT");
	float sr = conf->getNumericValue("Polycode", "uiWindowSkinR");
	float sb = conf->getNumericValue("Polycode", "uiWindowSkinB");
	float sl = conf->getNumericValue("Polycode", "uiWindowSkinL");
	
	topPadding = st;
	
	padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
	
	windowRect = new UIBox(conf->getStringValue("Polycode", "uiWindowSkin"),
						  st,sr,sb,sl,
						  width, height);	
	
	addChild(windowRect);
	
	titlebarRect = new ScreenShape(ScreenShape::SHAPE_RECT, width, st);
	titlebarRect->setColor(0,0,0,0);
	titlebarRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(titlebarRect);
	
	ScreenLabel *titleLabel = new ScreenLabel(fontName, windowName, fontSize, Label::ANTIALIAS_FULL);
	titleLabel->setPosition(conf->getNumericValue("Polycode", "uiWindowTitleX"),conf->getNumericValue("Polycode", "uiWindowTitleY"));
	addChild(titleLabel);
	
	closeBtn = new UIImageButton(conf->getStringValue("Polycode", "uiWindowCloseIcon"));
	addChild(closeBtn);
	closeBtn->setPosition(width-closeBtn->getWidth()-conf->getNumericValue("Polycode", "uiCloseIconX"), conf->getNumericValue("Polycode", "uiCloseIconY"));

	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	closeBtn->addEventListener(this, UIEvent::CLICK_EVENT);
	
	this->width = width;
	this->height = height;
	this->hitwidth = width;
	this->hitheight = height;
	
	focusable = true;
	blockMouseInput = true;
}

void UIWindow::setWindowSize(float w, float h) {
//	windowRect->setScale(w/windowRect->getWidth(), h/windowRect->getHeight());
//	shadowRect->setScale(w/shadowRect->getWidth(), h/shadowRect->getHeight());
//	titlebarRect->setScale((w-4)/titlebarRect->getWidth(), 1.0f);
//	closeBtn->setPosition(w-closeBtn->getWidth()-2, 4);
}

UIWindow::~UIWindow() {

}

void UIWindow::onKeyDown(TAUKey key, wchar_t charCode) {
	
	if(key == TAUK_TAB) {
		if(hasFocus) {
			focusNextChild();
		}
	}
	
	if(key == TAUK_ESCAPE && closeOnEscape) {
		onClose();
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);		
	}
}

void UIWindow::onLoseFocus() {
		if(focusedChild) {
			focusedChild->hasFocus = false;
			focusedChild->onLoseFocus();
		}
}

void UIWindow::onMouseDown(float x, float y) {
	if(hasFocus)
		return;
	hasFocus = true;
	dispatchEvent(new ScreenEvent(), ScreenEvent::ENTITY_MOVE_TOP);
	for(int i=0; i < children.size(); i++) {
		if(((ScreenEntity*)children[i])->isFocusable()) {
			focusChild(((ScreenEntity*)children[i]));
			return;
		}
	}
}

void UIWindow::showWindow() {
//	if(!visible) {
		visible = true;
		windowTween = new Tween(&color.a, Tween::EASE_IN_QUAD, 0.0f, 1.0f, 0.1f);
//	}
}

void UIWindow::hideWindow() {
//	if(visible) {
		windowTween = new Tween(&color.a, Tween::EASE_IN_QUAD, 1.0f, 0.0f, 0.1f);
		windowTween->addEventListener(this, Event::COMPLETE_EVENT);
//	}
}


void UIWindow::handleEvent(Event *event) {
	if(event->getDispatcher() == titlebarRect) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEUP:
				stopDrag();
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				startDrag(inputEvent->mousePosition.x,inputEvent->mousePosition.y);
			break;
		}
	}
	if(event->getDispatcher() == closeBtn) {
		onClose();
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
	}
	if(event->getDispatcher() == windowTween) {
		visible = false;
		windowTween->removeEventListener(this, Event::COMPLETE_EVENT);
	}
}