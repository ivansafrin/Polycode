#pragma once

#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyGLRenderer.h"
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
