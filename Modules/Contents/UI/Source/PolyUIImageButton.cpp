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

#include "PolyUIImageButton.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"

using namespace Polycode;

UIImageButton::UIImageButton(String imageName) : UIElement() {
	setAnchorPoint(-1.0, -1.0, 0.0);
	
	buttonImage = new SceneImage(imageName.c_str());
	addChild(buttonImage);
	buttonImage->depthTest = false;
	buttonImage->setAnchorPoint(-1.0, -1.0, 0.0);
	
	buttonRect = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, buttonImage->getWidth(),buttonImage->getHeight(),0,0);
	buttonRect->setColor(1,1,1,0);
	buttonRect->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(buttonRect);
	
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	buttonRect->processInputEvents = true;
	pressedDown = false;
	
	setWidth(buttonRect->getWidth());
	setHeight(buttonRect->getHeight());	
}

void UIImageButton::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonRect) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEOVER:
				this->setColor(0.7,0.7,0.7,1);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				pressedDown = false;
				this->setColor(1,1,1,1);
			break;
			case InputEvent::EVENT_MOUSEUP:
				this->setColor(0.7,0.7,0.7,1);				
				if(pressedDown) {
					dispatchEvent(new UIEvent(), UIEvent::CLICK_EVENT);
				}
				pressedDown = false;				
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				pressedDown = true;
				this->setColor(0.5,0.5,0.5,1);				
			break;
		}
	}
}

UIImageButton::~UIImageButton() {
	if(!ownsChildren) {
		delete buttonImage;
		delete buttonRect;
	}
}
