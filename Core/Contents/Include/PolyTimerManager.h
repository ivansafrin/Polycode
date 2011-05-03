/*
 *  PolyTimerManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/18/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package Services

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyTimer.h"
#include "PolyCoreServices.h"
#include <vector>

using std::vector;

namespace Polycode {

	class Timer;

	class _PolyExport TimerManager {
		public:
		TimerManager();
		~TimerManager();
		
		void removeTimer(Timer *timer);
		void addTimer(Timer *timer);
		void Update();
		
		private:
		
		vector <Timer*> timers;
	};
}