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
#include "PolycodeRemoteDebugger.h"

PolycodeConsole* PolycodeConsole::instance = NULL;

BackTraceEntry::BackTraceEntry(String fileName, int lineNumber, PolycodeProject *project) : UIElement() {


	this->project = project;
	this->fileName = fileName;
	this->lineNumber = lineNumber;

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	

	labelBg = new ScreenShape(ScreenShape::SHAPE_RECT, 20,20);
	labelBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	labelBg->setColor(0.0, 0.0, 0.0, 0.15);
	labelBg->processInputEvents = true;
	addChild(labelBg);	
	
	labelBg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	label = new ScreenLabel(fileName+" on line "+String::IntToString(lineNumber), fontSize, fontName);
	addChild(label);
	label->setPosition(5,2);
	
}

void BackTraceEntry::handleEvent(Event *event) {
	if(event->getDispatcher() == labelBg) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			Select();
		}
	}
}

void BackTraceEntry::Select() {
	BackTraceEvent *event = new BackTraceEvent();
	event->fileName = fileName;
	event->lineNumber = lineNumber;
	event->project = project;		
	
	dispatchEvent(event, BackTraceEvent::EVENT_BACKTRACE_SELECTED);
		
	labelBg->setColor(0.0, 0.0, 1.0, 0.35);
}

void BackTraceEntry::Deselect() {
	labelBg->setColor(0.0, 0.0, 0.0, 0.15);
}


BackTraceEntry::~BackTraceEntry() {
	delete label;
	delete labelBg;
}

void BackTraceEntry::Resize(Number width, Number height) {
	labelBg->setShapeSize(width, 20);

}

BackTraceWindow::BackTraceWindow() : UIElement() {

	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");		

	labelBg = new ScreenShape(ScreenShape::SHAPE_RECT, 20,30);
	labelBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	labelBg->setColor(0.1, 0.1, 0.1, 1.0);
	addChild(labelBg);
	
	ScreenLabel *label = new ScreenLabel("CRASH STACK", 22, "section");
	label->color.a = 0.3;
	addChild(label);
	label->setPosition(5,0);
	
}	

void BackTraceWindow::Resize(Number width, Number height) {
	labelBg->setShapeSize(width, 30);
	this->width = width;
	this->height = height;
	adjustEntries();
}

void BackTraceWindow::adjustEntries() {
	for(int i=0; i < entries.size(); i++) {
		entries[i]->Resize(width, 20);
		entries[i]->setPosition(0, 30 + (i * 21));
	}
}

void BackTraceWindow::handleEvent(Event *event) {
	for(int i=0; i < entries.size(); i++) {
		if(event->getDispatcher() == entries[i]) {
			if(event->getEventCode() == BackTraceEvent::EVENT_BACKTRACE_SELECTED && event->getEventType() == "BackTraceEvent") {
				for(int j=0; j < entries.size(); j++) {
					entries[j]->Deselect();
				}
				BackTraceEvent *btEvent = (BackTraceEvent*) event;
												
				BackTraceEvent *_event = new BackTraceEvent();
				_event->fileName = btEvent->fileName;
				_event->lineNumber = btEvent->lineNumber;
				_event->project = btEvent->project;		
				
				dispatchEvent(_event, BackTraceEvent::EVENT_BACKTRACE_SELECTED);
			}
		}
	}
}

void BackTraceWindow::addBackTrace(String fileName, int lineNumber, PolycodeProject *project) {
	BackTraceEntry *entry = new BackTraceEntry(fileName, lineNumber, project);
	entry->addEventListener(this, BackTraceEvent::EVENT_BACKTRACE_SELECTED);
	entries.push_back(entry);
	addChild(entry);
	adjustEntries();	
	if(entries.size() == 1) {
		entry->Select();
	}
}

void BackTraceWindow::clearBackTraces() {
	for(int i=0; i < entries.size(); i++) {
		removeChild(entries[i]);
		entries[i]->removeAllHandlers();
		delete entries[i];
	}
	entries.clear();
	adjustEntries();
}

BackTraceWindow::~BackTraceWindow() {
	
}

PolycodeConsole::PolycodeConsole() : UIElement() {

	backtraceSizer = new UIHSizer(100,100,300,false);
	addChild(backtraceSizer);
	
	debugger = NULL;
	debugTextInput = new UITextInput(true, 100, 100);
	backtraceSizer->addLeftChild(debugTextInput);

	backtraceWindow = new BackTraceWindow();
	backtraceSizer->addRightChild(backtraceWindow);

	consoleTextInput = new UITextInput(false, 100, 100);
	addChild(consoleTextInput);	
	
	consoleTextInput->addEventListener(this, Event::COMPLETE_EVENT);
	
	consoleTextInput->setColor(0.95, 1.0, 0.647, 1.0);

	PolycodeConsole::setInstance(this);
}

PolycodeConsole::~PolycodeConsole() {

}

void PolycodeConsole::setDebugger(PolycodeRemoteDebugger *debugger) {
	this->debugger = debugger;
}

void PolycodeConsole::handleEvent(Event *event) {
	if(event->getDispatcher() == consoleTextInput) {
		if(event->getEventCode() == Event::COMPLETE_EVENT && event->getEventType() == "") {
			_print(">"+consoleTextInput->getText()+"\n");
			if(debugger) {
				if(!debugger->isConnected()) {
					_print("Unable to inject code. No debugger clients connected.\n");
				} else {
					debugger->injectCode(consoleTextInput->getText());
				}
			}	
			
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

void PolycodeConsole::addBacktrace(String fileName, int lineNumber, PolycodeProject *project) {
	instance->_addBacktrace(fileName, lineNumber, project);
}

void PolycodeConsole::_addBacktrace(String fileName, int lineNumber, PolycodeProject *project) {
	backtraceWindow->addBackTrace(fileName, lineNumber, project);
}

void PolycodeConsole::clearBacktraces() {
	instance->_clearBacktraces();
}

void PolycodeConsole::_clearBacktraces() {
	backtraceWindow->clearBackTraces();
}


void PolycodeConsole::_print(String msg) {
	debugTextInput->setText(debugTextInput->getText()+msg);
	debugTextInput->getScrollContainer()->setScrollValue(0, 1.0);
}

void PolycodeConsole::Resize(Number width, Number height) {
	backtraceSizer->Resize(width, height-25);
	backtraceSizer->setPosition(0, 0);

	consoleTextInput->Resize(width, 25);
	consoleTextInput->setPosition(0, height-25);
}