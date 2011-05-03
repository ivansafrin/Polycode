/*
 *  PolyEventHandler.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Events

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyEvent.h"

//#ifdef _COMPILE_LUA
#include "PolyLuaEventStuff.h"
//#endif

namespace Polycode {

	/**
	* Can handle events from EventDispatcher classes.
	*/
	class _PolyExport EventHandler {
		public:
			/**
			* Default constructor
			*/
			EventHandler();
			~EventHandler();

#ifdef _COMPILE_LUA
		SWIGLUA_REF onEvent;
#endif

		void secondaryHandler(Event *event);		
		
		/** 
		* This method gets called by an EventDispatcher that the handler is listening to if the dispatching event's code matches the code that handler is listening for. Typically, you subclass EventHandler and implement the handleEvent method to handle specific events.
		* @see EventDispatcher
		*/
		virtual void handleEvent(Event *event){}
			
		private:
	
	};
}
