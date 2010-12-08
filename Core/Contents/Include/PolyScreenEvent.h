/*
 *  PolyScreenEvent.h
 *  Poly
 *
 *  Created by Ivan Safrin on 8/27/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyGlobals.h"
#include "PolyEvent.h"

namespace Polycode {

	class _PolyExport ScreenEvent : public Event {
		public:
			ScreenEvent();
			~ScreenEvent();
		
			static const int ENTITY_MOVE_TOP = 0;
			static const int ENTITY_MOVE_BOTTOM = 1;
			static const int ENTITY_MOVE_UP = 2;
			static const int ENTITY_MOVE_DOWN = 3;
			
		protected:		
			
	};
}