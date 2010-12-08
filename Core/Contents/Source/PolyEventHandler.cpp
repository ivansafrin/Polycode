/*
 *  PolyEventHandler.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyEventHandler.h" 


namespace Polycode {
	
	EventHandler::EventHandler() {
#ifdef _COMPILE_LUA		
		onEvent.L = 0;
		onEvent.ref = 0;
#endif		
	}
	
	void EventHandler::secondaryHandler(Event *event) {
#ifdef _COMPILE_LUA				
		if(onEvent.L != 0)
			handlePolyLuaEvent(&onEvent, (void*)event);
#endif		
	}	
	
	EventHandler::~EventHandler() {
		
	}
	
}