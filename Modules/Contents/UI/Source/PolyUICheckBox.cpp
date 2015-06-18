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
#include "PolyCoreServices.h"
#include "PolyConfig.h"
#include "PolyRenderer.h"

using namespace Polycode;

UICheckBox::UICheckBox(String caption, bool checked) : UIElement() {

	Config *conf = CoreServices::getInstance()->getConfig();	
	Number uiScale = conf->getNumericValue("Polycode", "uiScale");
    
	String fontName = conf->getStringValue("Polycode", "uiCheckBoxFont");
	int fontSize = conf->getNumericValue("Polycode", "uiCheckBoxFontSize");	
	String checkImage = conf->getStringValue("Polycode", "uiCheckBoxCheckedImage");
	String uncheckImage = conf->getStringValue("Polycode", "uiCheckBoxUncheckedImage");
	Number checkboxTextOffsetX = conf->getNumericValue("Polycode", "uiCheckBoxLabelOffsetX");
	Number checkboxTextOffsetY = conf->getNumericValue("Polycode", "uiCheckBoxLabelOffsetY");
	
	this->checked = checked;
	
	buttonImageChecked = new UIImage(checkImage);
    buttonImageChecked->Resize(buttonImageChecked->getWidth() / uiScale, buttonImageChecked->getHeight() / uiScale);
	buttonImageChecked->visible = checked;

	buttonImageUnchecked = new UIImage(uncheckImage);
	buttonImageUnchecked->visible = !checked;
    buttonImageUnchecked->Resize(buttonImageUnchecked->getWidth() / uiScale, buttonImageUnchecked->getHeight() / uiScale);
	
	captionLabel = new UILabel(caption, fontSize, fontName, Label::ANTIALIAS_FULL);
	captionLabel->setBlendingMode(Renderer::BLEND_MODE_NORMAL);    
	addChild(captionLabel);
	captionLabel->setPosition(buttonImageChecked->getWidth() + checkboxTextOffsetX, checkboxTextOffsetY);
	
	addChild(buttonImageUnchecked);	
	addChild(buttonImageChecked);
	
	captionLabel->color.setColorHexFromString(conf->getStringValue("Polycode", "uiDefaultFontColor"));
	
	buttonImageUnchecked->addEventListener(this, InputEvent::EVENT_MOUSEOVER);
	buttonImageUnchecked->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	buttonImageUnchecked->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	buttonImageUnchecked->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	buttonImageUnchecked->processInputEvents = true;
	captionLabel->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	captionLabel->processInputEvents = true;
	
	setHeight(buttonImageUnchecked->getHeight());
	setWidth(buttonImageUnchecked->getWidth() + captionLabel->getWidth() + checkboxTextOffsetX);
}

String UICheckBox::getCaptionLabel() {
	return captionLabel->getText();
}

UICheckBox::~UICheckBox() {
	if(!ownsChildren) {
		delete buttonImageChecked;
		delete buttonImageUnchecked;
		delete captionLabel;
	}
}

bool UICheckBox::isChecked() {
	return checked;
}
		
void UICheckBox::setChecked(bool val) {
	checked = val;
	buttonImageChecked->visible = checked;
	buttonImageUnchecked->visible = !checked;
}

void UICheckBox::changeCheck() {
	checked = !checked;
	buttonImageChecked->visible = checked;
	buttonImageUnchecked->visible = !checked;
	dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);	
}
		
void UICheckBox::handleEvent(Event *event) {
	if(event->getDispatcher() == buttonImageUnchecked || event->getDispatcher() == captionLabel) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				changeCheck();
			break;
		}
	}
    UIElement::handleEvent(event);    
}
