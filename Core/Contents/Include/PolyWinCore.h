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
#include "PolyInputKeys.h"
#include "PolyRectangle.h"

#include <windows.h>
#include <windowsx.h>
#include <WinUser.h>

#include <vector>

#ifndef VK_0
#define VK_0	'0'
#define VK_1	'1'
#define VK_2	'2'
#define VK_3	'3'
#define VK_4	'4'
#define VK_5	'5'
#define VK_6	'6'
#define VK_7	'7'
#define VK_8	'8'
#define VK_9	'9'
#define VK_A	'A'
#define VK_B	'B'
#define VK_C	'C'
#define VK_D	'D'
#define VK_E	'E'
#define VK_F	'F'
#define VK_G	'G'
#define VK_H	'H'
#define VK_I	'I'
#define VK_J	'J'
#define VK_K	'K'
#define VK_L	'L'
#define VK_M	'M'
#define VK_N	'N'
#define VK_O	'O'
#define VK_P	'P'
#define VK_Q	'Q'
#define VK_R	'R'
#define VK_S	'S'
#define VK_T	'T'
#define VK_U	'U'
#define VK_V	'V'
#define VK_W	'W'
#define VK_X	'X'
#define VK_Y	'Y'
#define VK_Z	'Z'
#endif /* VK_0 */

/* These keys haven't been defined, but were experimentally determined */
#define VK_SEMICOLON	0xBA
#define VK_EQUALS	0xBB
#define VK_COMMA	0xBC
#define VK_MINUS	0xBD
#define VK_PERIOD	0xBE
#define VK_SLASH	0xBF
#define VK_GRAVE	0xC0
#define VK_LBRACKET	0xDB
#define VK_BACKSLASH	0xDC
#define VK_RBRACKET	0xDD
#define VK_APOSTROPHE	0xDE
#define VK_BACKTICK	0xDF
#define VK_OEM_102	0xE2

#define EXTENDED_KEYMASK	(1<<24)

namespace Polycode {

	class _PolyExport Win32Mutex : public CoreMutex {
	public:
		HANDLE winMutex; 
	};

	class _PolyExport Win32Event {
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
	
	class _PolyExport Win32Core : public Core {
		
	public:
		
		Win32Core(PolycodeViewBase *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate);
		~Win32Core();

		void enableMouse(bool newval);
		unsigned int getTicks();		
		bool Update();

		void handleKeyDown(LPARAM lParam, WPARAM wParam);
		void handleKeyUp(LPARAM lParam, WPARAM wParam);
		void handleMouseMove(LPARAM lParam, WPARAM wParam);
		void handleMouseWheel(LPARAM lParam, WPARAM wParam);
		void handleMouseDown(int mouseCode,LPARAM lParam, WPARAM wParam);
		void handleMouseUp(int mouseCode,LPARAM lParam, WPARAM wParam);

		void setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel);
		
		void initContext(bool usePixelFormat, unsigned int pixelFormat);
		void destroyContext();

		void createThread(Threaded *target);

		PolyKEY mapKey(LPARAM lParam, WPARAM wParam);

		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();

		void checkEvents();
		void initKeymap();

		void platformSleep(int msecs);

		std::vector<Polycode::Rectangle> getVideoModes();

		// NEED TO IMPLEMENT:

		void setCursor(int cursorType){ }
		void copyStringToClipboard(const String& str) { }
		String getClipboardString() { return ""; }

		void createFolder(const String& folderPath) {}
		void copyDiskItem(const String& itemPath, const String& destItemPath) {}
		void moveDiskItem(const String& itemPath, const String& destItemPath) {}
		String openFolderPicker()  { return "";}
		void removeDiskItem(const String& itemPath)  {}
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) { std::vector<String> ret; return ret;}
		void resizeTo(int xRes, int yRes) { }
		
	private:

		PolyKEY keyMap[1024];

		CoreMutex *eventMutex;

		std::vector<Win32Event> win32Events;

		void initMultisample(int numSamples);

		HWND hWnd;

		int lastMouseX;
		int lastMouseY;

		bool isFullScreen;

		HDC hDC;
		HGLRC hRC;
		unsigned int PixelFormat;
		PIXELFORMATDESCRIPTOR pfd;
		

	};
}
