/*
 Copyright (C) 2011 by Ivan Safrin
 
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

#include "PolyEventDispatcher.h"
#include "PolyEvent.h"

namespace Polycode {

	EventDispatcher::EventDispatcher() : EventHandler() {

	}

	EventDispatcher::~EventDispatcher() {

	}

	void EventDispatcher::addEventListener(EventHandler *handler, int eventCode) {
		EventEntry newEntry;
		newEntry.handler = handler;
		newEntry.eventCode = eventCode;
		handlerEntries.push_back(newEntry);
	}

	void EventDispatcher::removeAllHandlers() {
		handlerEntries.clear();
	}

	void EventDispatcher::removeAllHandlersForListener(EventHandler *handler) {
		std::vector<EventEntry>::iterator iter = handlerEntries.begin();
		while (iter != handlerEntries.end()) {	
			if((*iter).handler == handler) {
				iter = handlerEntries.erase(iter);
			} else {
				++iter;
			}
		}
		
	}

	void EventDispatcher::removeEventListener(EventHandler *handler, int eventCode) {
		for(int i=0;i<handlerEntries.size();i++) {
			if(handlerEntries[i].eventCode == eventCode && handlerEntries[i].handler == handler) {
				handlerEntries.erase(handlerEntries.begin()+i);
			}
		}
	}

	void EventDispatcher::__dispatchEvent(Event *event, int eventCode) {
		//		event->setDispatcher(dynamic_cast<void*>(this));
		event->setDispatcher(this);
		event->setEventCode(eventCode);
		for(int i=0;i<handlerEntries.size();i++) {
			if(handlerEntries[i].eventCode == eventCode) {
				//				if(handlerEntries[i].handler->onEvent != NULL) {
				//					handlerEntries[i].handler->onEvent(event);
				//				}
				handlerEntries[i].handler->handleEvent(event);
				handlerEntries[i].handler->secondaryHandler(event);
			}
		}

	}

	void EventDispatcher::dispatchEventNoDelete(Event *event, int eventCode) {
		__dispatchEvent(event,eventCode);
	}

	void EventDispatcher::dispatchEvent(Event *event, int eventCode) {
		__dispatchEvent(event,eventCode);
		delete event;
	}
}
