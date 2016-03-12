/*
 Copyright (C) 2016 by Joachim Meyer
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

#include <android/native_activity.h>

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyInputEvent.h"

#define POLYCODE_CORE AndroidCore

namespace Polycode {

	class PolycodeView;
// 	class ANativeActivity;
	
	class AndroidEvent {
	public:
		int eventGroup;
		int eventCode;

		int mouseX;
		int mouseY;

		std::vector<TouchInfo> touches;
		TouchInfo touch;

		PolyKEY keyCode;
		wchar_t unicodeChar;

		char mouseButton;
		long eventTime;

		static const int EVENTBASE_PLATFORMEVENT = 0x300;
		static const int INPUT_EVENT = EVENTBASE_PLATFORMEVENT + 0;
		static const int SYSTEM_FOCUS_EVENT = EVENTBASE_PLATFORMEVENT + 1;
	};


	class AndroidCoreMutex : public CoreMutex {
	public:
		void lock();
		void unlock();
		pthread_mutex_t pMutex;
	};

	class OpenGLGraphicsInterface;

	class _PolyExport AndroidCore : public Core {
	public:

		AndroidCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex = -1, bool retinaSupport = false);
		~AndroidCore();

		void Render();
		bool systemUpdate();
		
		void setCursor(int cursorType);
		
		void createThread(Threaded *target);
		CoreMutex *createMutex();
				
		void copyStringToClipboard(const String& str);
		String getClipboardString();
		
		void createFolder(const String& folderPath);
		void copyDiskItem(const String& itemPath, const String& destItemPath);
		void moveDiskItem(const String& itemPath, const String& destItemPath);
		void removeDiskItem(const String& itemPath);
		
		String openFolderPicker();
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
		String saveFilePicker(std::vector<CoreFileExtension> extensions);
		
		void handleVideoModeChange(VideoModeChangeInfo *modeInfo);
		void flushRenderContext();
		bool isWindowInitialized();
		
		void openURL(String url);
		
		unsigned int getTicks();
		
		String executeExternalCommand(String command, String args, String inDirectory);
		bool systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector);

		void handleSystemEvent(AndroidEvent systemEvent);
		void checkEvents();
		
		void setDeviceSize(Number x, Number y);

		Number getBackingXRes();
		Number getBackingYRes();
		
		CoreMutex* getEGLMutex();
		
		bool recreateContext;
	private:

		PolycodeView* view;
		
		Number deviceWidth;
		Number deviceHeight;

		int lastMouseY;
		int lastMouseX;

		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;
		
		CoreMutex* eglMutex;

		std::vector<AndroidEvent> systemInputEvents;

		double pcFreq;

		OpenGLGraphicsInterface *graphicsInterface;

	};
}
