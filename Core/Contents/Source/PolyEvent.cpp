/*
 *  PolyEvent.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyEvent.h"

namespace Polycode {
	
	Event::Event() {
			eventType = "Event";
	}
	
	Event::Event(int eventCode) {
		eventType = "Event";		
		setEventCode(eventCode);
	}
	
	Event::~Event() {
		
	}
	
	String Event::getEventType() {
		return eventType;
	}
	
	int Event::getEventCode() {
		return eventCode;
	}
	
	EventDispatcher *Event::getDispatcher() {
		return dispatcher;
	}
	
	void Event::setDispatcher(EventDispatcher *dispatcher) {
		this->dispatcher = dispatcher;
	}
	
	void Event::setEventCode(int eventCode) {
		this->eventCode = eventCode;
	}
}