/*
 *  PolyTimer.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyEventDispatcher.h"
#include "PolyCoreServices.h"

using namespace std;

namespace Polycode {
	
	class _PolyExport Timer : public EventDispatcher {
		public:
			Timer(bool triggerMode, int msecs);
			~Timer();

		void Pause(bool paused);
		bool isPaused();
		unsigned int getTicks();
		void Update(unsigned int ticks);
		void Reset();
		bool hasElapsed();
		Number getElapsedf();		

		static const int EVENT_TRIGGER = 0;
		
		private:
			
			int elapsed;
			bool paused;
			unsigned int msecs;
			bool triggerMode;
			unsigned int last;
			unsigned int ticks;
	};
}