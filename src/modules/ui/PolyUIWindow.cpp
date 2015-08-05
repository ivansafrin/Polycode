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
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyTweenManager.h"
#include "PolyRenderer.h"

using namespace Polycode;


UIWindow::UIWindow(String windowName, Number width, Number height) : UIElement() {
	closeOnEscape = false;
	
	snapToPixels = true;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
    
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
	
	Number titleBarHeight = conf->getNumericValue("Polycode", "uiWindowTitleBarHeight");
	Number titleBarOffset = conf->getNumericValue("Polycode", "uiWindowTitleBarOffset");
		
	titlebarRect = new Entity();
    titlebarRect->setWidth(width);
    titlebarRect->setHeight(titleBarHeight);
    titlebarRect->visible = false;
	titlebarRect->setPosition(0, titleBarOffset);
	titlebarRect->setAnchorPoint(-1.0, -1.0, 0.0);
	titlebarRect->processInputEvents = true;
	addChild(titlebarRect);
	
	titleLabel = new SceneLabel(windowName, fontSize, fontName, Label::ANTIALIAS_FULL);
    titleLabel->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	titleLabel->setPosition(conf->getNumericValue("Polycode", "uiWindowTitleX"),conf->getNumericValue("Polycode", "uiWindowTitleY"));
	addChild(titleLabel);
	titleLabel->color.setColorHexFromString(conf->getStringValue("Polycode", "uiWindowFontColor"));
	titleLabel->positionAtBaseline = false;
	titleLabel->setAnchorPoint(-1.0, -1.0, 0.0);
			
	closeBtn = new UIImageButton(conf->getStringValue("Polycode", "uiWindowCloseIcon"), uiScale);
	addChild(closeBtn);
	closeIconX = conf->getNumericValue("Polycode", "uiCloseIconX");
	closeIconY = conf->getNumericValue("Polycode", "uiCloseIconY");
	
	closeBtn->setPosition(width-closeBtn->getWidth()-closeIconX, closeIconY);	
	
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	titlebarRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	closeBtn->addEventListener(this, UIEvent::CLICK_EVENT);
	
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	
	setWidth(width);
	setHeight(height);
	
	focusable = true;
	blockMouseInput = true;
	
	processInputEvents = true;
}

void UIWindow::setWindowCaption(String caption) {
	titleLabel->setText(caption);
}

void UIWindow::setWindowSize(Number w, Number h) {
	w = w+(padding*2.0);
	h = h+topPadding;

	windowRect->resizeBox(w, h);
	setWidth(w);
	setHeight(h);	
	closeBtn->setPosition(getWidth()-closeBtn->getWidth()-closeIconX, closeIconY);	
	matrixDirty = true;
}

UIWindow::~UIWindow() {
	if(!ownsChildren) {
		delete windowRect;
		delete titlebarRect;
		delete titleLabel;
		delete closeBtn;
	}
	CoreServices::getInstance()->getCore()->getInput()->removeAllHandlersForListener(this);
}

void UIWindow::onKeyDown(PolyKEY key, wchar_t charCode) {	
	if(key == KEY_ESCAPE && closeOnEscape) {
		onClose();
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);		
	}
}

void UIWindow::onLoseFocus() {
/*
		if(focusedChild) {
			focusedChild->hasFocus = false;
			focusedChild->onLoseFocus();
		}
*/		
}

void UIWindow::onMouseDown(Number x, Number y) {
	if(hasFocus)
		return;
	hasFocus = true;

	if(focusChildren.size() > 0) {
		focusChild(focusChildren[0]);
	}
}

void UIWindow::showWindow() {
	enabled = true;
	visible = true;
}

void UIWindow::hideWindow() {
	visible = false;
	enabled = false;
}

void UIWindow::onClose() {
    visible = false;
    enabled = false;
}

void UIWindow::handleEvent(Event *event) {

	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			onKeyDown(inputEvent->key, inputEvent->charCode);
		}
	}

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
}
