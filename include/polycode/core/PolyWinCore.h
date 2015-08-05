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
#include "PolyInputEvent.h"
#include "PolyRectangle.h"

#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>

#include <mmsystem.h>
#include <regstr.h>


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

#define NO_TOUCH_API
#define NO_PEN_API

#ifdef _MINGW
#define NO_TOUCH_API 1
#define NO_PEN_API 1
#endif

#define POLYCODE_CORE Win32Core

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
		TouchInfo touch;
		std::vector<TouchInfo> touches;
		int touchType;
		PolyKEY keyCode;
		wchar_t unicodeChar;		
		char mouseButton;	
		static const int EVENTBASE_PLATFORMEVENT = 0x300;
		static const int INPUT_EVENT = EVENTBASE_PLATFORMEVENT+0;
	};
	
	
	class HIDGamepadAxis {
		public:
		//IOHIDElementCookie cookie;
		//CFIndex logicalMin;
		//CFIndex logicalMax;
		bool hasNullState;
		bool isHatSwitch;
		bool isHatSwitchSecondAxis;
	};

	class HIDGamepadButton {
		public:
		//IOHIDElementCookie cookie;
		int something;
	};	
	
class Gamepad_devicePrivate {
public:
	UINT joystickID;
	JOYINFOEX lastState;
	int xAxisIndex;
	int yAxisIndex;
	int zAxisIndex;
	int rAxisIndex;
	int uAxisIndex;
	int vAxisIndex;
	int povXAxisIndex;
	int povYAxisIndex;
	UINT (* axisRanges)[2];
};


	class GamepadDeviceEntry  {
		public:
			GamepadDeviceEntry() {
				numAxes = 0;
			}
			std::vector<HIDGamepadAxis> axisElements;
			std::vector<HIDGamepadButton> buttonElements;			
			unsigned int deviceID;
			//IOHIDDeviceRef device;
			unsigned int numAxes;
			unsigned int numButtons;	
			Gamepad_devicePrivate *privateData;
		//	CoreInput *input;		
	};

	class _PolyExport Win32Core : public Core {
		
	public:
		
		Win32Core(PolycodeViewBase *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate,  int monitorIndex = -1, bool retinaSupport = false);
		~Win32Core();

		void enableMouse(bool newval);
		void captureMouse(bool newval);
		void warpCursor(int x, int y);
		unsigned int getTicks();		
		bool systemUpdate();
		void Render();
		void setVSync(bool vSyncVal);

		void handleKeyDown(LPARAM lParam, WPARAM wParam, wchar_t unicodeChar);
		void handleKeyUp(LPARAM lParam, WPARAM wParam);
		void handleMouseMove(LPARAM lParam, WPARAM wParam);
		void handleMouseWheel(LPARAM lParam, WPARAM wParam);
		void handleMouseDown(int mouseCode,LPARAM lParam, WPARAM wParam);
		void handleMouseUp(int mouseCode,LPARAM lParam, WPARAM wParam);
		void handleTouchEvent(LPARAM lParam, WPARAM wParam);
		void handlePointerUpdate(LPARAM lParam, WPARAM wParam);

		bool isMultiTouchEnabled() { return hasMultiTouch; }

		void setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, bool retinaSupport = true);
		
		void initContext(int aaLevel);
		void destroyContext();

		void getWglFunctionPointers();

		void createThread(Threaded *target);

		PolyKEY mapKey(LPARAM lParam, WPARAM wParam);

		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();

		void checkEvents();
		void initKeymap();

		void platformSleep(int msecs);

		std::vector<Polycode::Rectangle> getVideoModes();

		void handleAxisChange(GamepadDeviceEntry * device, int axisIndex, DWORD value);
		void handleButtonChange(GamepadDeviceEntry * device, DWORD lastValue, DWORD value);
		void handlePOVChange(GamepadDeviceEntry * device, DWORD lastValue, DWORD value);

		void detectGamepads();
		void initGamepad();
		void shutdownGamepad();
		void Gamepad_processEvents();

		void initTouch();

		void handleViewResize(int width, int height);
		
		String executeExternalCommand(String command,  String args, String inDirectory);
		std::vector<String> openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple);
		String saveFilePicker(std::vector<CoreFileExtension> extensions);

		void createFolder(const String& folderPath);
		void openURL(String url);
		String openFolderPicker();
		void copyDiskItem(const String& itemPath, const String& destItemPath);
		void moveDiskItem(const String& itemPath, const String& destItemPath);
		void removeDiskItem(const String& itemPath);

		Number getBackingXRes();
		Number getBackingYRes();

		void setCursor(int cursorType);

		void copyStringToClipboard(const String& str);
		String getClipboardString();

		void resizeTo(int xRes, int yRes) { }
		
		std::vector<GamepadDeviceEntry*> gamepads;

		HWND hWnd;
		HINSTANCE hInstance;
		bool hasCopyDataString;
		String copyDataString;

	private:

		Number scaleFactor;
		bool checkSpecialKeyEvents(PolyKEY key);

		unsigned int nextDeviceID;
		PolyKEY keyMap[1024];
		unsigned int lastGamepadDetect;

		std::vector<Win32Event> win32Events;

		int lastMouseX;
		int lastMouseY;

		bool isFullScreen;
		bool retinaSupport;
		bool resizable;

		HDC hDC;
		HGLRC hRC;
		
		// frequency of the windows performance counter
		double pcFreq;

		// Tracks whether the system supports multitouch at runtime
		bool hasMultiTouch;

		std::vector<TouchInfo> pointerTouches;
		
#ifndef NO_TOUCH_API
		// Create generic reference to any multitouch functions we need, so that we
		// can make them available at runtime if the operating system supports it
		// while still allowing fallback for older systems
		// See: http://msdn.microsoft.com/en-us/library/ms683212(v=vs.85).aspx
		typedef bool (WINAPI *GetTouchInputInfoType)(HTOUCHINPUT,UINT,PTOUCHINPUT,int);
		GetTouchInputInfoType GetTouchInputInfoFunc;
#endif	
	};
}
