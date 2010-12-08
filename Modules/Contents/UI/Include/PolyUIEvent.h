/*
 *  PolyUIEvent.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package UI

#pragma once
#include "PolyGlobals.h"
#include "PolyEvent.h"

namespace Polycode {

	class _PolyExport UIEvent : public Event {
		public:
			UIEvent();
			~UIEvent();
		
			static const int CLICK_EVENT = 0;
			static const int CLOSE_EVENT = 1;
			static const int OK_EVENT = 2;
			static const int CANCEL_EVENT = 3;
			static const int CHANGE_EVENT = 4;
			
		protected:
		
			
	};
}