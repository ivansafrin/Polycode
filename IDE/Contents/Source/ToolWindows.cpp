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
 
#include "ToolWindows.h"

TextInputPopup::TextInputPopup() : UIWindow(L"", 300, 80) {
	
	textInput = new UITextInput(false, 290, 12);	
	addChild(textInput);
	textInput->setPosition(padding, 35);
		
	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(cancelButton);
	cancelButton->setPosition(padding+300-100-100-10, 64);		
	
	okButton = new UIButton(L"OK", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addChild(okButton);
	okButton->setPosition(padding+300-100, 64);
	
	closeOnEscape = true;

}

void TextInputPopup::setCaption(String caption) {
	setWindowCaption(caption);
}

String TextInputPopup::getValue() {
	return textInput->getText();
}

void TextInputPopup::setValue(String value) {
	textInput->setText(value);
	focusChild(textInput);	
}

void TextInputPopup::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);						
			}
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);				
			}									
		}
	}
	UIWindow::handleEvent(event);	
}


TextInputPopup::~TextInputPopup() {
	
}

YesNoPopup::YesNoPopup() : UIWindow(L"", 300, 80) {
	
	captionLabel = new SceneLabel("This is a caption", 12);	
	addChild(captionLabel);
	captionLabel->setPosition(padding, 35);
		
	buttonAnchor = new Entity();
	buttonAnchor->processInputEvents = true;
	addChild(buttonAnchor);
			
	cancelButton = new UIButton(L"No", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	buttonAnchor->addChild(cancelButton);
	cancelButton->setPosition(0, 60);		
	
	okButton = new UIButton(L"Yes", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	buttonAnchor->addChild(okButton);
	okButton->setPosition(120, 60);
	
	closeOnEscape = true;

}

void YesNoPopup::setCaption(String caption) {
	captionLabel->setText(caption);
	
	Number windowSize = captionLabel->getWidth() + 50;
	if(windowSize < 400)
		windowSize = 400;
	setWindowSize(windowSize, 80);
	captionLabel->setPosition(padding + (windowSize - captionLabel->getWidth()) / 2.0, 35);
	buttonAnchor->setPosition(padding + ((windowSize - 220) / 2.0), 0);
}

void YesNoPopup::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::OK_EVENT);						
			}
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
				dispatchEvent(new UIEvent(), UIEvent::CANCEL_EVENT);				
			}									
		}
	}
	UIWindow::handleEvent(event);	
}


YesNoPopup::~YesNoPopup() {
	
}

YesNoCancelPopup::YesNoCancelPopup() : UIWindow(L"", 300, 80) {
	
	captionLabel = new SceneLabel("This is a caption", 12);	
	addChild(captionLabel);
	captionLabel->setPosition(padding, 35);
		
	buttonAnchor = new Entity();
	buttonAnchor->processInputEvents = true;
	addChild(buttonAnchor);
	
	noButton = new UIButton(L"No", 100);
	noButton->addEventListener(this, UIEvent::CLICK_EVENT);
	buttonAnchor->addChild(noButton);
	noButton->setPosition(0, 60);		
	
	okButton = new UIButton(L"Yes", 100);
	okButton->addEventListener(this, UIEvent::CLICK_EVENT);
	buttonAnchor->addChild(okButton);
	okButton->setPosition(120, 60);
	
	cancelButton = new UIButton(L"Cancel", 100);
	cancelButton->addEventListener(this, UIEvent::CLICK_EVENT);
	buttonAnchor->addChild(cancelButton);
	cancelButton->setPosition(240, 60);		

	closeOnEscape = true;

}

void YesNoCancelPopup::setCaption(String caption) {
	captionLabel->setText(caption);
	Number windowSize = captionLabel->getWidth() + 50;
	if(windowSize < 400)
		windowSize = 400;	
	setWindowSize(windowSize, 80);
	captionLabel->setPosition(padding + (windowSize - captionLabel->getWidth()) / 2.0, 35);
	buttonAnchor->setPosition(padding + ((windowSize - 360) / 2.0), 0);
}

void YesNoCancelPopup::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent") {
		if(event->getEventCode() == UIEvent::CLICK_EVENT) {
			if(event->getDispatcher() == okButton) {
				dispatchEvent(new UIEvent(), UIEvent::YES_EVENT);						
			}
			
			if(event->getDispatcher() == noButton) {
				dispatchEvent(new UIEvent(), UIEvent::NO_EVENT);
			}									
			
			if(event->getDispatcher() == cancelButton) {
				dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
				dispatchEvent(new UIEvent(), UIEvent::CANCEL_EVENT);				
			}									
			
		}
	}
	UIWindow::handleEvent(event);	
}


YesNoCancelPopup::~YesNoCancelPopup() {
	
}