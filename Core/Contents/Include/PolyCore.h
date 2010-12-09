/*
 *  PolyCore.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/12/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Core

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyRenderer.h"
#include "PolyThreaded.h"
#include "PolyCoreInput.h"
//#include "PolyGLRenderer.h"
#include "PolyMaterialManager.h"
#include "PolyCoreServices.h"
#include "PolyRectangle.h"
#include <vector>
#include <string>

#define CURSOR_ARROW 0
#define CURSOR_TEXT 1
#define CURSOR_POINTER 2
#define CURSOR_CROSSHAIR 3
#define CURSOR_RESIZE_LEFT_RIGHT 4
#define CURSOR_RESIZE_UP_DOWN 5

using std::vector;
using std::wstring;

long getThreadID();

namespace Polycode {

	class CoreServices;

	class _PolyExport CoreMutex {
	public:
		int mutexID;
	};
	
	class _PolyExport CoreFileExtension {
	public:
		String extension;
		String description;
	};
	
	class _PolyExport Core : public EventDispatcher {

	public:
		Core(int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		virtual ~Core();
		
		virtual bool Update() = 0;
		virtual unsigned int getTicks() = 0;
		virtual void enableMouse(bool newval);
		
		virtual void setCursor(int cursorType) = 0;
		
		virtual void createThread(Threaded *target) = 0;

		virtual void lockMutex(CoreMutex *mutex) = 0;
		virtual void unlockMutex(CoreMutex *mutex) = 0;
		virtual CoreMutex *createMutex() = 0;
		
		virtual void copyStringToClipboard(String str) = 0;
		virtual String getClipboardString() = 0;
		
		CoreServices *getServices();
		float getFPS();
		void Shutdown();
		
		bool isFullscreen(){ return fullScreen; }
		int getAALevel() { return aaLevel; }
				
		CoreInput *getInput();
		float getXRes();
		float getYRes();
		
		int getNumVideoModes();
		virtual vector<Rectangle> getVideoModes() = 0;
		
		
		virtual void createFolder(String folderPath) = 0;
		virtual void copyDiskItem(String itemPath, String destItemPath) = 0;		
		virtual void moveDiskItem(String itemPath, String destItemPath) = 0;		
		virtual void removeDiskItem(String itemPath) = 0;

		virtual String openFolderPicker() = 0;
		virtual vector<string> openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) = 0;
		
		void setVideoModeIndex(int index, bool fullScreen, int aaLevel);
		virtual void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel) = 0;
		virtual void resizeTo(int xRes, int yRes) = 0;
		
		void doSleep();
		
		float getElapsed();	
		float getTicksFloat();
		
		void setUserPointer(void *ptr) { userPointer = ptr; }
		void *getUserPointer() { return userPointer; }
		
		static const int EVENT_CORE_RESIZE = 0;		
		
	protected:
		
		void *userPointer;
		
		long refreshInterval;
		
		bool fullScreen;
		int aaLevel;
	
		vector<Vector2>	videoModes;
		void updateCore();

		int numVideoModes;
		
		bool running;
		float fps;
		unsigned int frameTicks;
		unsigned int lastFrameTicks;
		unsigned int lastFPSTicks;
		unsigned int elapsed;
		
		bool mouseEnabled;
		
		unsigned int lastSleepFrameTicks;
		
		int xRes;
		int yRes;		
		
		int frames;
		
		CoreInput *input;
		Renderer *renderer;
		CoreServices *services;
	};
	
}