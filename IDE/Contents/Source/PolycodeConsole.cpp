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

#include "PolycodeConsole.h"

PolycodeConsole* PolycodeConsole::instance = NULL;

PolycodeConsole::PolycodeConsole() : UIElement() {
	debugTextInput = new UITextInput(true, 100, 100);
	addChild(debugTextInput);

	consoleTextInput = new UITextInput(false, 100, 100);
	addChild(consoleTextInput);	
	
	consoleTextInput->addEventListener(this, Event::COMPLETE_EVENT);
	
	consoleTextInput->setColor(0.95, 1.0, 0.647, 1.0);

	PolycodeConsole::setInstance(this);
}

PolycodeConsole::~PolycodeConsole() {

}

void PolycodeConsole::handleEvent(Event *event) {
	if(event->getDispatcher() == consoleTextInput) {
		if(event->getEventCode() == Event::COMPLETE_EVENT) {
			_print(">"+consoleTextInput->getText());
			_print("\n");
			consoleTextInput->setText("");
		}
	}
}

void PolycodeConsole::setInstance(PolycodeConsole *newInstance) {
	instance = newInstance;
}

void PolycodeConsole::print(String msg) {
	instance->_print(msg);
}

void PolycodeConsole::_print(String msg) {
	debugTextInput->setText(debugTextInput->getText()+msg);
	debugTextInput->
}

void PolycodeConsole::Resize(Number width, Number height) {
	debugTextInput->Resize(width, height-25);
	debugTextInput->setPosition(0, 0);

	consoleTextInput->Resize(width, 25);
	consoleTextInput->setPosition(0, height-25);
}