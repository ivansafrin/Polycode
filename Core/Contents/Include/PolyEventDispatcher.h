/*
 *  PolyEventDispatcher.h
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
#include "PolyEventHandler.h"
#include "PolyEvent.h"
#include <vector>

using std::vector;


namespace Polycode {


typedef struct {
	EventHandler *handler;
	int eventCode;
} EventEntry;

	class _PolyExport EventDispatcher : public EventHandler {
		public:
			EventDispatcher();
			virtual ~EventDispatcher();
			
			void removeAllHandlers();
			void removeAllHandlersForListener(void *listener);
			void addEventListener(EventHandler *handler, int eventCode);
			void removeEventListener(EventHandler *handler, int eventCode);
			void __dispatchEvent(Event *event, int eventCode);		
			void dispatchEvent(Event *event, int eventCode);
			void dispatchEventNoDelete(Event *event, int eventCode);
		
		protected:
	
		vector<EventEntry> handlerEntries;
	
	};
}