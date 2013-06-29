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
#include <vector>

#define POLYCODE_CORE SDLCore

struct SDL_mutex;

namespace Polycode {

class PolycodeView;

class _PolyExport SDLCoreMutex : public CoreMutex {
	public:
		SDL_mutex *pMutex;
};

class _PolyExport SDLCore : public Core {

	public:

		SDLCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex=-1);
		~SDLCore();

		void enableMouse(bool newval);
		void captureMouse(bool);
		unsigned int getTicks();
		bool Update();
		void Render();
		void setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel);
		void createThread(Threaded *target);
		std::vector<Rectangle> getVideoModes();

		void setCursor(int cursorType);
		void warpCursor(int x, int y);
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();
		void copyStringToClipboard(const String& str);
		String getClipboardString();
		void createFolder(const String& folderPath);
		void copyDiskItem(const String& itemPath, const String& destItemPath);
		void moveDiskItem(const String& itemPath, const String& destItemPath);
		void removeDiskItem(const String& itemPath);
		String openFolderPicker();
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
		void resizeTo(int xRes, int yRes);

		String executeExternalCommand(String command, String args, String inDirectory="");
		void openURL(String url);


	private:
		bool checkSpecialKeyEvents(PolyKEY key);

		uint32_t flags;
		bool resizableWindow;

};

}
