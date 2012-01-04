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

#include "PolyUICheckBox.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"

using namespace Polycode;

UICheckBox::UICheckBox(Font *font, String checkImage, String caption, bool checked) : ScreenEntity() {
	buttonImage = new ScreenImage(checkImage.c_str());
	buttonImage->setPosition(2, 3);
	this->checked = checked;
	buttonImage->visible = checked;
	
	captionLabel = new ScreenLabel(caption, 11, "", Label::ANTIALIAS_FULL);
	addChild(captionLabel);
	captionLabel->setPosition(buttonImage->getWidth()+14,0);
	
	buttonRect = new ScreenShape(ScreenShape::SHAPE_RECT, buttonImage->getWidth()+5,buttonImage->getHeight()+5,0,0);
	buttonRect->setColor(0.1f, 0.1f, 0.1f, 1.0f);
	buttonRect->strokeEnabled = true;
	buttonRect->setStrokeColor(1.0f, 1.0f, 1.0f, 0.1f);
	addChild(buttonRect);
	addChild(buttonImage);
	
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	captionLabel->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
}

UICheckBox::~UICheckBox() {

}

bool UICheckBox::isChecked() {
	return checked;
}
		
void UICheckBox::changeCheck() {
	checked = !checked;
	buttonImage->visible = checked;
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}
		
void UICheckBox::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonRect || event->getDispatcher() == captionLabel) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				changeCheck();
			break;
		}
	}
}
