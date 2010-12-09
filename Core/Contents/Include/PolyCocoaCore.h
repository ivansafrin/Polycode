/*
 *  PolyCocoaCore.h
 *  Poly
 *
 *  Created by Ivan Safrin on 2/16/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

// @package Core

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyString.h"
#include "PolyRectangle.h"
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include "PolyGLRenderer.h"
#include <mach/mach_time.h>

#import <Cocoa/Cocoa.h>

using std::vector;

@class SubstanceView;

namespace Polycode {
	
	class _PolyExport PosixMutex : public CoreMutex {
	public:
		pthread_mutex_t pMutex;
	};
	
	class CocoaEvent {
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
	
	class _PolyExport CocoaCore : public Core {		
	public:
		
		CocoaCore(SubstanceView *view, int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		virtual ~CocoaCore();
		
		void enableMouse(bool newval);
		unsigned int getTicks();		
		bool Update();		
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);		
		void resizeTo(int xRes, int yRes);
		void createThread(Threaded *target);		
		
		void createFolder(String folderPath);
		void copyDiskItem(String itemPath, String destItemPath);
		void moveDiskItem(String itemPath, String destItemPath);		
		void removeDiskItem(String itemPath);		
		String openFolderPicker();
		vector<string> openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple);
		
		void setCursor(int cursorType);
		
		void copyStringToClipboard(String str);
		String getClipboardString();		
		
//		static pascal OSStatus coreEventHandler (EventHandlerCallRef next, EventRef event, void *data);	
		
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();		
		
		void checkEvents();
		
		vector<Rectangle> getVideoModes();
		
		int lastMouseY;
		int lastMouseX;		
		
		CoreMutex *eventMutex;
		
		vector<CocoaEvent> cocoaEvents;
		
		NSOpenGLContext *context;
		
	private:	
		SubstanceView *glView;
		
		uint64_t initTime;		
				
	};
}