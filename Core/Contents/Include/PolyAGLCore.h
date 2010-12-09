/*
 *  PolyAGLCore.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Core

#pragma once
#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyRectangle.h"
#include "PolyString.h"
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include "PolyGLRenderer.h"
#include <AGL/agl.h>
#include <AGL/aglRenderers.h>
#include <mach/mach_time.h>

using std::vector;

namespace Polycode {
	
	class _PolyExport PosixMutex : public CoreMutex {
	public:
		pthread_mutex_t pMutex;
	};
	
	class OSXEvent {
	public:
		int eventGroup;
		int eventCode;
		
		int mouseX;
		int mouseY;
		
		TAUKey keyCode;
		wchar_t unicodeChar;
		
		char mouseButton;
		
		static const int INPUT_EVENT = 0;
	};
	
	class _PolyExport AGLCore : public Core {
		
	public:
		
		AGLCore(WindowRef window, Polycode::Rectangle *clippingArea, int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		virtual ~AGLCore();
		
		void enableMouse(bool newval);
		unsigned int getTicks();		
		bool Update();		
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);		
		void createThread(Threaded *target);		
		
		static pascal OSStatus coreEventHandler (EventHandlerCallRef next, EventRef event, void *data);	
		
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();		
		
		void checkEvents();
		
		vector<Rectangle> getVideoModes();
		
		int lastMouseY;
		int lastMouseX;		
		
		CoreMutex *eventMutex;
		
		vector<OSXEvent> osxEvents;
		
	private:
		
		
		uint64_t initTime;
		WindowRef mainWindow;
		AGLContext aglContext;	
		
	};
}