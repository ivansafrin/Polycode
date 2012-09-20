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


#include "PolyUIWindow.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"

using namespace Polycode;


UIWindow::UIWindow(String windowName, Number width, Number height) : ScreenEntity() {
	
	closeOnEscape = false;
	
	snapToPixels = true;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	
	String fontName = conf->getStringValue("Polycode", "uiWindowTitleFont");
	int fontSize = conf->getNumericValue("Polycode", "uiWindowTitleFontSize");	
	
	Number st = conf->getNumericValue("Polycode", "uiWindowSkinT");
	Number sr = conf->getNumericValue("Polycode", "uiWindowSkinR");
	Number sb = conf->getNumericValue("Polycode", "uiWindowSkinB");
	Number sl = conf->getNumericValue("Polycode", "uiWindowSkinL");
	
	topPadding = st;
	
	padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
	
	width = width+(padding*2.0);
	height = height+topPadding;
	
	windowRect = new UIBox(conf->getStringValue("Polycode", "uiWindowSkin"),
						  st,sr,sb,sl,
						  width, height);	
	
	addChild(windowRect);
	
	titlebarRect = new ScreenShape(ScreenShape::SHAPE_RECT, width, st);
	titlebarRect->setColor(0,0,0,0);
	titlebarRect->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	titlebarRect->processInputEvents = true;
	addChild(titlebarRect);
	
	ScreenLabel *titleLabel = new ScreenLabel(windowName, fontSize, fontName, Label::ANTIALIAS_FULL);
	titleLabel->setPosition(conf->getNumericValue("Polycode", "uiWindowTitleX"),conf->getNumericValue("Polycode", "uiWindowTitleY"));
	addChild(titleLabel);
	
	closeBtn = new UIImageButton(conf->getStringValue("Polycode", "uiWindowCloseIcon"));
	addChild(closeBtn);
	closeBtn->setPosition(width-closeBtn->getWidth()-conf->getNumericValue("Polycode", "uiCloseIconX"), conf->getNumericValue("Polycode", "uiCloseIconY"));

	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	closeBtn->addEventListener(this, UIEvent::CLICK_EVENT);
	
	this->width = width;
	this->height = height;
	setHitbox(width, height);
	
	focusable = true;
	blockMouseInput = true;
}

void UIWindow::setWindowSize(Number w, Number h) {
//	windowRect->setScale(w/windowRect->getWidth(), h/windowRect->getHeight());
//	shadowRect->setScale(w/shadowRect->getWidth(), h/shadowRect->getHeight());
//	titlebarRect->setScale((w-4)/titlebarRect->getWidth(), 1.0f);
//	closeBtn->setPosition(w-closeBtn->getWidth()-2, 4);
}

UIWindow::~UIWindow() {

}

void UIWindow::onKeyDown(PolyKEY key, wchar_t charCode) {
	
	if(key == KEY_TAB) {
		if(hasFocus) {
			focusNextChild();
		}
	}
	
	if(key == KEY_ESCAPE && closeOnEscape) {
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

void UIWindow::onMouseDown(Number x, Number y) {
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
		enabled = true;
		visible = true;
		windowTween = new Tween(&color.a, Tween::EASE_IN_QUAD, 0.0f, 1.0f, 0.01f);
//	}
}

void UIWindow::hideWindow() {
//	if(visible) {
		windowTween = new Tween(&color.a, Tween::EASE_IN_QUAD, 1.0f, 0.0f, 0.01f);
		windowTween->addEventListener(this, Event::COMPLETE_EVENT);
//	}
}


void UIWindow::handleEvent(Event *event) {
	if(event->getDispatcher() == titlebarRect) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
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
		enabled = false;		
		windowTween->removeEventListener(this, Event::COMPLETE_EVENT);
	}
}