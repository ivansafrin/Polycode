/*
 *  PolyUITreeEvent.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package UI

#pragma once

#include "PolyGlobals.h"
#include "PolyEvent.h"
#include "PolyUITree.h"

namespace Polycode {
	class UITree;
	class _PolyExport UITreeEvent : public Event {
		public:
			UITreeEvent(UITree *selection);
			UITreeEvent();
			~UITreeEvent();
		
			static const int NEED_REFRESH_EVENT = 2000;
			static const int SELECTED_EVENT = 2001;
			static const int EXECUTED_EVENT = 2002;
			
			UITree *selection;

		protected:
		
			
	};
}