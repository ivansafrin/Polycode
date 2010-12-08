/*
 *  PolyEventDispatcher.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyEventDispatcher.h"

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
	
	void EventDispatcher::removeAllHandlersForListener(void *listener) {
		for(int i=0;i<handlerEntries.size();i++) {
			if(handlerEntries[i].handler == listener) {
				handlerEntries.erase(handlerEntries.begin()+i);
				i--;
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