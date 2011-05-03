/*
 *  ScreenManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/15/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Services

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyScreen.h"
//#include "PolyPhysicsScreen.h"
#include "PolyCoreServices.h"
#include <vector>

using std::vector;

namespace Polycode {

	class Screen;

	class _PolyExport ScreenManager : public EventDispatcher {
		public:
		ScreenManager();
		~ScreenManager();
		
//		Screen *createScreen(int screenType);
		void removeScreen(Screen *screen);
		void addScreen(Screen* screen);
		void Update();
		
		void handleEvent(Event *event);
		
		static const int REGULAR_SCREEN = 1;
		static const int PHYSICS_SCREEN = 2;
		
		private:
		
		vector <Screen*> screens;
			
	};

}