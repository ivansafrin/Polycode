/*
 *  PolyiPhoneCore.h
 *  Poly
 *
 *  Created by Ivan Safrin on 2/1/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package Core

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyRectangle.h"
#include <vector>

using std::vector;

namespace Polycode {
	
	class _PolyExport PosixMutex : public CoreMutex {
	public:
		pthread_mutex_t pMutex;
	};
	
	class iPhoneEvent {
	public:
		int eventGroup;
		int eventCode;
		
		int mouseX;
		int mouseY;
		
		PolyKEY keyCode;
		wchar_t unicodeChar;
		
		char mouseButton;
		
		static const int INPUT_EVENT = 0;
	};
	
	class _PolyExport IPhoneCore : public Core {
		
	public:
		
		IPhoneCore(int frameRate);
		virtual ~IPhoneCore();
		
		void enableMouse(bool newval);
		unsigned int getTicks();		
		bool Update();		
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);		
		void createThread(Threaded *target);				
		
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();		
		
		void checkEvents();
		
		vector<Rectangle> getVideoModes();
		
		int lastMouseY;
		int lastMouseX;		
		
		CoreMutex *eventMutex;
		
		vector<iPhoneEvent> osxEvents;
		
	private:
		
		
	};
}