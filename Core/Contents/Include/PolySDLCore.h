/*
 Copyright (C) 2011 by Ivan Safrin
 
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

#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyGLRenderer.h"
#include "PolyGLSLShaderModule.h"
#include "PolyRectangle.h"
#include <vector>
#include <SDL/SDL.h>
#include <iostream>

using std::vector;

namespace Polycode {

	class _PolyExport SDLCoreMutex : public CoreMutex {
	public:
		SDL_mutex *pMutex;
	};

	class _PolyExport SDLCore : public Core {
		
	public:
		
		SDLCore(PolycodeViewBase *view, int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		~SDLCore();

		void enableMouse(bool newval);
		unsigned int getTicks();
		bool Update();
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);
		void createThread(Threaded *target);
		vector<Rectangle> getVideoModes();
		
		void setCursor(int cursorType);
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();
		void copyStringToClipboard(String str);
		String getClipboardString();
		void createFolder(String folderPath);
		void copyDiskItem(String itemPath, String destItemPath);		
		void moveDiskItem(String itemPath, String destItemPath);		
		void removeDiskItem(String itemPath);
		String openFolderPicker();
		vector<string> openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple);
		void resizeTo(int xRes, int yRes);

	private:
		
		
		
	};
}
