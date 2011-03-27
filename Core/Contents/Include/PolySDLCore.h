/*
 *  PolySDLCore.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Core
/*

#pragma once
#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyRectangle.h"
#include <vector>

using std::vector;

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
#endif

#ifdef COMPILE_SDL_CORE

namespace Polycode {
	class _PolyExport SDLCore : public Core {
		
	public:
		
		SDLCore(int xRes, int yRes, bool fullScreen, int aaLevel);
		~SDLCore();

		void enableMouse(bool newval);
		unsigned int getTicks();
		
		bool Update();
		
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);
		
		void createThread(Threaded *target);
		
		vector<Rectangle> getVideoModes();
		
	private:
		
		
		
	};
}

#endif

*/