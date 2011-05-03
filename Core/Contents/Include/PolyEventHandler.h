/*
 *  PolyEventHandler.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
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

	class _PolyExport EventHandler {
		public:
			EventHandler();
			~EventHandler();

		virtual void secondaryHandler(Event *event);		
		virtual void handleEvent(Event *event){}
			
		void *secondaryHandlerData;
		
		
		private:
	
	};
}
