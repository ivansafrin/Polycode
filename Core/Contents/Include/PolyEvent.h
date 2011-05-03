/*
 *  PolyEvent.h
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
#include <string>

using std::string;

namespace Polycode {

	class EventDispatcher;
	class _PolyExport Event {
		public:
			Event();
			Event(int eventCode);
			~Event();
			
			int getEventCode();
			void setEventCode(int eventCode);
			EventDispatcher *getDispatcher();
			void setDispatcher(EventDispatcher *dispatcher);
			String getEventType();
			
			static const int COMPLETE_EVENT = 0;
			static const int CHANGE_EVENT = 1;
						
		protected:
			
			String eventType;
			EventDispatcher *dispatcher;
			int eventCode;
			
	};
}