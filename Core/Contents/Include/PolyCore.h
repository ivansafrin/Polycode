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
	
	/**
	* The main core of the framework. The core deals with system-level functions, such as window initialization and OS interaction. Each platform has its own implementation of this base class. NOTE: SOME OF THE FUNCTIONALITY IN THE CORE IS NOT FULLY IMPLEMENTED!!
	*/
	class _PolyExport Core : public EventDispatcher {

	public:
	
		/**
		* Constructor.
		* @param xRes Inital horizontal resolution of the renderer.
		* @param yRes Inital vertical resolution of the renderer.		
		* @param fullScreen True to launch in fullscreen, false to launch in window.
		* @param aaLevel Level of anti-aliasing. Possible values are 2,4 and 6.
		* @param frameRate Frame rate that the core will update and render at.
		*/			
		Core(int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		virtual ~Core();
		
		virtual bool Update() = 0;

		
		/**
		* Show or hide cursor.
		* @param newval True to show mouse, false to hide it.
		*/		
		virtual void enableMouse(bool newval);
		
		/**
		* Sets the cursor the application is using.
		* @param cursorType Type of cursor to use. Possible values are CURSOR_ARROW, CURSOR_TEXT, CURSOR_POINTER, CURSOR_CROSSHAIR, CURSOR_RESIZE_LEFT_RIGHT, CURSOR_RESIZE_UP_DOWN
		*/
		virtual void setCursor(int cursorType) = 0;
		
		/**
		* Launches a Threaded class into its own thread. See the documentation for Threaded for information on how to crated threaded classes.
		* @param target Target threaded class.
		* @see Threaded
		*/		
		virtual void createThread(Threaded *target) = 0;

		/**
		* Locks a mutex.
		* @param mutex Mutex to lock.
		*/
		virtual void lockMutex(CoreMutex *mutex) = 0;
		
		/**
		* Unlocks a mutex.
		* @param mutex Mutex to lock.
		*/		
		virtual void unlockMutex(CoreMutex *mutex) = 0;
		
		/**
		* Creates a mutex
		* @return Newly created mutex.
		*/				
		virtual CoreMutex *createMutex() = 0;
		
		/**
		* Copies the specified string to system clipboard.
		* @param str String to copy to clipboard.
		*/
		virtual void copyStringToClipboard(String str) = 0;
		
		/**
		* Returns the system clipboard as a string.
		* @return String from clipboard.
		*/		
		virtual String getClipboardString() = 0;
		
		/**
		* Returns the core services. See CoreServices for a detailed explanation of services.
		* @return Core services.
		@see CoreServices
		*/
		CoreServices *getServices();
		
		/**
		* Returns the current average frames per second.
		* @return Current average frames per second.
		*/		
		Number getFPS();
		
		/**
		* Shuts down the core and quits the application.
		*/
		void Shutdown();

		/**
		* Checks if core is in fullscreen mode.
		* @return True if in full screen, false if otherwise.
		*/		
		bool isFullscreen(){ return fullScreen; }
		
		/**
		* Returns the current anti-aliasing level.
		* @return Current anti-aliasing level.
		*/				
		int getAALevel() { return aaLevel; }

		/**
		* Returns the input class. See CoreInput for details in input.
		* @return Input class.
		* @see CoreInput
		*/					
		CoreInput *getInput();
		
		/**
		* Returns current horizontal resolution.
		* @return Current horizontal resolution.
		*/											
		Number getXRes();
		
		/**
		* Returns current vertical resolution.
		* @return Current vertical resolution.
		*/													
		Number getYRes();
		
		// deprecated
		int getNumVideoModes();
		
		/**
		* Returns the available system video modes. 
		* @return An STL vector of video modes.
		*/															
		virtual vector<Rectangle> getVideoModes() = 0;
				
		/**
		* Creates a folder on disk with the specified path.
		* @param folderPath Path to create the folder in.
		*/																			
		virtual void createFolder(String folderPath) = 0;
		
		/**
		* Copies a disk item from one path to another
		* @param itemPath Path to the item to copy.
		* @param destItemPath Destination path to copy to.
		*/																					
		virtual void copyDiskItem(String itemPath, String destItemPath) = 0;		
		
		/**
		* Moves a disk item from one path to another
		* @param itemPath Path to the item to move.
		* @param destItemPath Destination path to move to.
		*/																							
		virtual void moveDiskItem(String itemPath, String destItemPath) = 0;		
		
		/**
		* Removes a disk item.
		* @param itemPath Path to the item to remove.
		*/																							
		virtual void removeDiskItem(String itemPath) = 0;

		/**
		* Opens a system folder picker and suspends operation.
		* @return The selected path returned from the picker.
		*/																					
		virtual String openFolderPicker() = 0;
		
		/**
		* Opens a system file picker for the specified extensions.
		* @param extensions An STL vector containing the allowed file extensions that can be selected.
		* @param allowMultiple If set to true, the picker can select multiple files.
		* @return An STL vector of the selected file paths.
		*/																							
		virtual vector<string> openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) = 0;
		
		void setVideoModeIndex(int index, bool fullScreen, int aaLevel);
		
		/**
		* Sets a new video mode.
		* @param xRes New horizontal resolution of the renderer.
		* @param yRes New vertical resolution of the renderer.		
		* @param fullScreen True to launch in fullscreen, false to launch in window.
		* @param aaLevel Level of anti-aliasing. Possible values are 2,4 and 6.
		*/																									
		virtual void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel) = 0;
		
		/**
		* Resizes the renderer.
		* @param xRes New horizontal resolution of the renderer.
		* @param yRes New vertical resolution of the renderer.		
		*/
		virtual void resizeTo(int xRes, int yRes) = 0;
		
		void doSleep();
		
		/**
		* Returns the time elapsed since last frame.
		* @return Time elapsed since last frame in floating point microseconds.
		*/
		Number getElapsed();	
		
		/**
		* Returns the total ticks elapsed since launch.
		* @return Time elapsed since launch in milliseconds
		*/						
		virtual unsigned int getTicks() = 0;		
		
		/**
		* Returns the total ticks elapsed since launch.
		* @return Time elapsed since launch in floating point microseconds.
		*/		
		Number getTicksFloat();
		
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
		Number fps;
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