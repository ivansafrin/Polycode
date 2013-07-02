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

#include "PolyWinCore.h"
#include "PolyGLHeaders.h"
#include "PolyCoreInput.h"
#include "PolyCoreServices.h"
#include "PolyInputEvent.h"
#include "PolyGLRenderer.h"
#include "PolyGLSLShaderModule.h"
#include "PolyLogger.h"
#include "PolyThreaded.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#include <Shlobj.h>
#include <Shellapi.h>
#include <Commdlg.h>

#if !defined(_MINGW)
PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;
#endif

using namespace Polycode;

long getThreadID() {
	return 0;
}

extern Win32Core *core;

void ClientResize(HWND hWnd, int nWidth, int nHeight)
{
  RECT rcClient, rcWindow;
  POINT ptDiff;
  GetClientRect(hWnd, &rcClient);
  GetWindowRect(hWnd, &rcWindow);
  ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
  ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
  MoveWindow(hWnd,rcWindow.left, rcWindow.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
}

void Core::getScreenInfo(int *width, int *height, int *hz) {
	DEVMODE mode = {}; // Zero initialize
	mode.dmSize = sizeof(DEVMODE);
	
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode);
	
    // Store the current display settings.
    if (width) *width = mode.dmPelsWidth;
    if (height) *height = mode.dmPelsHeight;
    if (hz) *hz = mode.dmDisplayFrequency;
}

Win32Core::Win32Core(PolycodeViewBase *view, int _xRes, int _yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate,  int monitorIndex) 
	: Core(_xRes, _yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

	hWnd = *((HWND*)view->windowData);
	core = this;

	char *buffer = _getcwd(NULL, 0);
	defaultWorkingDirectory = String(buffer);
	free(buffer);

	WCHAR path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path))) {
		userHomeDirectory = String(path);
	}


	initKeymap();
	initGamepad();
	initTouch();

	hDC = NULL;
	hRC = NULL;
	PixelFormat = 0;

	this->aaLevel = 999;
	
	lastMouseX = -1;
	lastMouseY = -1;

	eventMutex = createMutex();

	isFullScreen = fullScreen;

	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);

	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
		
	WSADATA WsaData;
	if(WSAStartup( MAKEWORD(2,2), &WsaData ) != NO_ERROR ){
		Logger::log("Error initializing sockets!\n");
	}

	((OpenGLRenderer*)renderer)->initOSSpecific();

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) wglGetProcAddress("wglGetSwapIntervalEXT");
	
	setVSync(vSync);

	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
}

Win32Core::~Win32Core() {
	shutdownGamepad();
	destroyContext();
}

void Win32Core::enableMouse(bool newval) {
	ShowCursor(newval);

	Core::enableMouse(newval);
}

void Win32Core::captureMouse(bool newval) {
	// Capture the mouse in the window holding
	// our polycode screen.
	SetCapture(hWnd);

	Core::captureMouse(newval);
}

void Win32Core::warpCursor(int x, int y) {
	POINT point;
	point.x = x;
	point.y = y;
	ClientToScreen(hWnd, &point);
	SetCursorPos(point.x,point.y);
	lastMouseX = x;
	lastMouseY = y;
}

unsigned int Win32Core::getTicks() {
	return GetTickCount();
}

void Win32Core::Render() {
	renderer->BeginRender();
	services->Render();
	renderer->EndRender();
	SwapBuffers(hDC);
}

bool Win32Core::Update() {
	if(!running)
		return false;
	doSleep();
	checkEvents();
	Gamepad_processEvents();
	updateCore();
	return running;
}

void Win32Core::setVSync(bool vSyncVal) {
	if(wglSwapIntervalEXT) {
		if(vSyncVal) {
			wglSwapIntervalEXT(1);
		} else {
			wglSwapIntervalEXT(0);
		}
	}
}

void Win32Core::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel) {

	bool resetContext = false;

	if(aaLevel != this->aaLevel) {
		resetContext = true;
	}

	this->xRes = xRes;
	this->yRes = yRes;
	this->fullScreen = fullScreen;
	this->aaLevel = aaLevel;

	if(fullScreen) {

		SetWindowLong(hWnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
		ShowWindow(hWnd, SW_SHOW);

		DEVMODE dmScreenSettings;					// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= xRes;			// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= yRes;			// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;				// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);

		SetWindowPos(hWnd, NULL, 0, 0, xRes, yRes, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	} else {
	//	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPED|WS_SYSMENU);
	//	ShowWindow(hWnd, SW_SHOW);
		ClientResize(hWnd, xRes, yRes);
	}


	isFullScreen = fullScreen;

	if(resetContext) {
		initContext(false, 0);

		if(aaLevel > 0) {
			initMultisample(aaLevel);
		}
	}

	setVSync(vSync);

	renderer->setAnisotropyAmount(anisotropyLevel);
	renderer->Resize(xRes, yRes);

	core->dispatchEvent(new Event(), Core::EVENT_CORE_RESIZE);
}

void Win32Core::initContext(bool usePixelFormat, unsigned int pixelFormat) {

	destroyContext();

   memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)) ;
   pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR); 
   pfd.nVersion   = 1 ; 
   pfd.dwFlags    = PFD_DOUBLEBUFFER |
                    PFD_SUPPORT_OPENGL |
                    PFD_DRAW_TO_WINDOW ;
   pfd.iPixelType = PFD_TYPE_RGBA ;
   pfd.cColorBits = 24;
   pfd.cDepthBits = 16;
   pfd.cAccumBlueBits = 8;	
   pfd.cAccumRedBits = 8;	
   pfd.cAccumGreenBits = 8;
   pfd.cAccumAlphaBits = 8;
   pfd.cAccumBits = 24;
   pfd.iLayerType = PFD_MAIN_PLANE ;


	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		Logger::log("Can't Create A GL Device Context.\n");
		return;							// Return FALSE
	}

	if(usePixelFormat) {
		PixelFormat = pixelFormat;
	} else {
		if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
		{
			Logger::log("Can't Find A Suitable PixelFormat.\n");
			return;							// Return FALSE
		}
	}

	Logger::log("Setting format: %d\n", PixelFormat);
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// Are We Able To Set The Pixel Format?
	{
		Logger::log("Can't Set The PixelFormat: %d.\n", PixelFormat);
		return;							// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		Logger::log("Can't Create A GL Rendering Context.\n");
		return;							// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		Logger::log("Can't Activate The GL Rendering Context.\n");
		return;							// Return FALSE
	}
}

void Win32Core::destroyContext() {

	if(hDC == NULL)
		return;

	wglMakeCurrent (hDC, 0);
	wglDeleteContext(hRC);
	hRC = 0;
	ReleaseDC (hWnd, hDC);
	hDC = 0;
	if (isFullScreen)
		ChangeDisplaySettings (NULL,0);
}

void Win32Core::initMultisample(int numSamples) {

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =
		(PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

	if (!wglChoosePixelFormatARB) {
		Logger::log("Multisampling not supported!\n");
		return;
	}
	int pixelFormat;
	UINT numFormats;
	float fAttributes[] = {0,0};

	int iAttributes[] = { WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB,24,
		WGL_DEPTH_BITS_ARB,24,
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		WGL_ACCUM_GREEN_BITS_ARB, 8,
		WGL_ACCUM_RED_BITS_ARB, 8,
		WGL_ACCUM_BLUE_BITS_ARB, 8,
		WGL_ACCUM_ALPHA_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
		WGL_SAMPLES_ARB, numSamples ,
		0,0};

		if(!wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats)) {
			Logger::log("Invalid pixel format chosen\n");
			return;
		}
		
	//	initContext(true, pixelFormat);

		glEnable(GL_MULTISAMPLE_ARB);
}

void Win32Core::initKeymap() {
	
	for (int i=0; i<1024; ++i )
		keyMap[i] = KEY_UNKNOWN;

	keyMap[VK_BACK] = KEY_BACKSPACE;
	keyMap[VK_TAB] = KEY_TAB;
	keyMap[VK_CLEAR] = KEY_CLEAR;
	keyMap[VK_RETURN] = KEY_RETURN;
	keyMap[VK_PAUSE] = KEY_PAUSE;
	keyMap[VK_ESCAPE] = KEY_ESCAPE;
	keyMap[VK_SPACE] = KEY_SPACE;
	keyMap[VK_APOSTROPHE] = KEY_QUOTE;
	keyMap[VK_COMMA] = KEY_COMMA;
	keyMap[VK_MINUS] = KEY_MINUS;
	keyMap[VK_PERIOD] = KEY_PERIOD;
	keyMap[VK_SLASH] = KEY_SLASH;
	keyMap[VK_0] = KEY_0;
	keyMap[VK_1] = KEY_1;
	keyMap[VK_2] = KEY_2;
	keyMap[VK_3] = KEY_3;
	keyMap[VK_4] = KEY_4;
	keyMap[VK_5] = KEY_5;
	keyMap[VK_6] = KEY_6;
	keyMap[VK_7] = KEY_7;
	keyMap[VK_8] = KEY_8;
	keyMap[VK_9] = KEY_9;
	keyMap[VK_SEMICOLON] = KEY_SEMICOLON;
	keyMap[VK_EQUALS] = KEY_EQUALS;
	keyMap[VK_LBRACKET] = KEY_LEFTBRACKET;
	keyMap[VK_BACKSLASH] = KEY_BACKSLASH;
	keyMap[VK_OEM_102] = KEY_LESS;
	keyMap[VK_RBRACKET] = KEY_RIGHTBRACKET;
	keyMap[VK_GRAVE] = KEY_BACKQUOTE;
	keyMap[VK_BACKTICK] = KEY_BACKQUOTE;
	keyMap[VK_A] = KEY_a;
	keyMap[VK_B] = KEY_b;
	keyMap[VK_C] = KEY_c;
	keyMap[VK_D] = KEY_d;
	keyMap[VK_E] = KEY_e;
	keyMap[VK_F] = KEY_f;
	keyMap[VK_G] = KEY_g;
	keyMap[VK_H] = KEY_h;
	keyMap[VK_I] = KEY_i;
	keyMap[VK_J] = KEY_j;
	keyMap[VK_K] = KEY_k;
	keyMap[VK_L] = KEY_l;
	keyMap[VK_M] = KEY_m;
	keyMap[VK_N] = KEY_n;
	keyMap[VK_O] = KEY_o;
	keyMap[VK_P] = KEY_p;
	keyMap[VK_Q] = KEY_q;
	keyMap[VK_R] = KEY_r;
	keyMap[VK_S] = KEY_s;
	keyMap[VK_T] = KEY_t;
	keyMap[VK_U] = KEY_u;
	keyMap[VK_V] = KEY_v;
	keyMap[VK_W] = KEY_w;
	keyMap[VK_X] = KEY_x;
	keyMap[VK_Y] = KEY_y;
	keyMap[VK_Z] = KEY_z;
	keyMap[VK_DELETE] = KEY_DELETE;

	keyMap[VK_NUMPAD0] = KEY_KP0;
	keyMap[VK_NUMPAD1] = KEY_KP1;
	keyMap[VK_NUMPAD2] = KEY_KP2;
	keyMap[VK_NUMPAD3] = KEY_KP3;
	keyMap[VK_NUMPAD4] = KEY_KP4;
	keyMap[VK_NUMPAD5] = KEY_KP5;
	keyMap[VK_NUMPAD6] = KEY_KP6;
	keyMap[VK_NUMPAD7] = KEY_KP7;
	keyMap[VK_NUMPAD8] = KEY_KP8;
	keyMap[VK_NUMPAD9] = KEY_KP9;
	keyMap[VK_DECIMAL] = KEY_KP_PERIOD;
	keyMap[VK_DIVIDE] = KEY_KP_DIVIDE;
	keyMap[VK_MULTIPLY] = KEY_KP_MULTIPLY;
	keyMap[VK_SUBTRACT] = KEY_KP_MINUS;
	keyMap[VK_ADD] = KEY_KP_PLUS;

	keyMap[VK_UP] = KEY_UP;
	keyMap[VK_DOWN] = KEY_DOWN;
	keyMap[VK_RIGHT] = KEY_RIGHT;
	keyMap[VK_LEFT] = KEY_LEFT;
	keyMap[VK_INSERT] = KEY_INSERT;
	keyMap[VK_HOME] = KEY_HOME;
	keyMap[VK_END] = KEY_END;
	keyMap[VK_PRIOR] = KEY_PAGEUP;
	keyMap[VK_NEXT] = KEY_PAGEDOWN;

	keyMap[VK_F1] = KEY_F1;
	keyMap[VK_F2] = KEY_F2;
	keyMap[VK_F3] = KEY_F3;
	keyMap[VK_F4] = KEY_F4;
	keyMap[VK_F5] = KEY_F5;
	keyMap[VK_F6] = KEY_F6;
	keyMap[VK_F7] = KEY_F7;
	keyMap[VK_F8] = KEY_F8;
	keyMap[VK_F9] = KEY_F9;
	keyMap[VK_F10] = KEY_F10;
	keyMap[VK_F11] = KEY_F11;
	keyMap[VK_F12] = KEY_F12;
	keyMap[VK_F13] = KEY_F13;
	keyMap[VK_F14] = KEY_F14;
	keyMap[VK_F15] = KEY_F15;

	keyMap[VK_NUMLOCK] = KEY_NUMLOCK;
	keyMap[VK_CAPITAL] = KEY_CAPSLOCK;
	keyMap[VK_SCROLL] = KEY_SCROLLOCK;
	keyMap[VK_RSHIFT] = KEY_RSHIFT;
	keyMap[VK_LSHIFT] = KEY_LSHIFT;
	keyMap[VK_RCONTROL] = KEY_RCTRL;
	keyMap[VK_LCONTROL] = KEY_LCTRL;
	keyMap[VK_RMENU] = KEY_RALT;
	keyMap[VK_LMENU] = KEY_LALT;
	keyMap[VK_RWIN] = KEY_RSUPER;
	keyMap[VK_LWIN] = KEY_LSUPER;

	keyMap[VK_HELP] = KEY_HELP;
	keyMap[VK_SNAPSHOT] = KEY_PRINT;
	keyMap[VK_CANCEL] = KEY_BREAK;
	keyMap[VK_APPS] = KEY_MENU;
	

}

void Win32Core::handleViewResize(int width, int height) {
	this->xRes = width;
	this->yRes = height;
	renderer->Resize(width, height);
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);
}

PolyKEY Win32Core::mapKey(LPARAM lParam, WPARAM wParam) {
		switch (wParam) {
				case VK_CONTROL:
					if ( lParam&EXTENDED_KEYMASK )
						wParam = VK_RCONTROL;
					else
						wParam = VK_LCONTROL;
					break;
				case VK_MENU:
					if ( lParam&EXTENDED_KEYMASK )
						wParam = VK_RMENU;
					else
						wParam = VK_LMENU;
					break;
				case VK_SHIFT:
					// Use MapVirtualKey to determine whether it's LSHIFT or RSHIFT by scancode.
					UINT scancode = (lParam & 0x00ff0000) >> 16;
					wParam = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
					break;
			}

	return keyMap[(unsigned int)wParam];
}

void Win32Core::handleKeyDown(LPARAM lParam, WPARAM wParam, wchar_t unicodeChar) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
	newEvent.keyCode = mapKey(lParam, wParam);
	newEvent.unicodeChar = unicodeChar;
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

void Win32Core::handleKeyUp(LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYUP;
	newEvent.keyCode = mapKey(lParam, wParam);
	newEvent.unicodeChar = 0;
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

#ifndef NO_TOUCH_API
void Win32Core::handleTouchEvent(LPARAM lParam, WPARAM wParam) {
	
	// Bail out now if multitouch is not available on this system
	if ( hasMultiTouch == false )
	{
		return;
	}
	
	lockMutex(eventMutex);

	int iNumContacts = LOWORD(wParam);
	HTOUCHINPUT hInput       = (HTOUCHINPUT)lParam;
    TOUCHINPUT *pInputs      = new TOUCHINPUT[iNumContacts];
       
    if(pInputs != NULL) {
		if(GetTouchInputInfoFunc(hInput, iNumContacts, pInputs, sizeof(TOUCHINPUT))) {

			std::vector<TouchInfo> touches;
			for(int i = 0; i < iNumContacts; i++) {
				TOUCHINPUT ti = pInputs[i];
				TouchInfo touchInfo;
				touchInfo.id = (int) ti.dwID;

				POINT pt;
				pt.x = TOUCH_COORD_TO_PIXEL(ti.x);
				pt.y = TOUCH_COORD_TO_PIXEL(ti.y);
				ScreenToClient(hWnd, &pt);
				touchInfo.position.x = pt.x; 
				touchInfo.position.y = pt.y;

				touches.push_back(touchInfo);
			}
              for(int i = 0; i < iNumContacts; i++) {
					TOUCHINPUT ti = pInputs[i];
					if (ti.dwFlags & TOUCHEVENTF_UP) {
						Win32Event newEvent;
						newEvent.eventGroup = Win32Event::INPUT_EVENT;
						newEvent.eventCode = InputEvent::EVENT_TOUCHES_ENDED;
						newEvent.touches = touches;
						newEvent.touch = touches[i];
						win32Events.push_back(newEvent);	
					} else if(ti.dwFlags & TOUCHEVENTF_MOVE) {
						Win32Event newEvent;
						newEvent.eventGroup = Win32Event::INPUT_EVENT;
						newEvent.eventCode = InputEvent::EVENT_TOUCHES_MOVED;
						newEvent.touches = touches;
						newEvent.touch = touches[i];
						win32Events.push_back(newEvent);
					} else if(ti.dwFlags & TOUCHEVENTF_DOWN) {
						Win32Event newEvent;
						newEvent.eventGroup = Win32Event::INPUT_EVENT;
						newEvent.eventCode = InputEvent::EVENT_TOUCHES_BEGAN;
						newEvent.touches = touches;
						newEvent.touch = touches[i];
						win32Events.push_back(newEvent);
					}
			  }
		}
	}
	unlockMutex(eventMutex);	
}
#endif

void Win32Core::handleMouseMove(LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_MOUSEMOVE;
	newEvent.mouseX = GET_X_LPARAM(lParam);
	newEvent.mouseY = GET_Y_LPARAM(lParam);	
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}
void Win32Core::handleMouseWheel(LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.mouseX = GET_X_LPARAM(lParam);
	newEvent.mouseY = GET_Y_LPARAM(lParam);
	int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	if(zDelta < 0)
		newEvent.eventCode = InputEvent::EVENT_MOUSEWHEEL_DOWN;
	else
		newEvent.eventCode = InputEvent::EVENT_MOUSEWHEEL_UP;
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

void Win32Core::handleMouseDown(int mouseCode,LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.mouseX = GET_X_LPARAM(lParam);
	newEvent.mouseY = GET_Y_LPARAM(lParam);
	newEvent.eventCode = InputEvent::EVENT_MOUSEDOWN;
	newEvent.mouseButton = mouseCode;
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

void Win32Core::handleMouseUp(int mouseCode,LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.mouseX = GET_X_LPARAM(lParam);
	newEvent.mouseY = GET_Y_LPARAM(lParam);
	newEvent.eventCode = InputEvent::EVENT_MOUSEUP;
	newEvent.mouseButton = mouseCode;
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

bool Win32Core::checkSpecialKeyEvents(PolyKEY key) {
	
	if(key == KEY_a && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_SELECT_ALL);
		return true;
	}
	
	if(key == KEY_c && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_COPY);
		return true;
	}
	
	if(key == KEY_x && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_CUT);
		return true;
	}
	
	
	if(key == KEY_y && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_REDO);
		return true;
	}
		
	if(key == KEY_z  && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_UNDO);
		return true;
	}
	
	if(key == KEY_v && (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL))) {
		dispatchEvent(new Event(), Core::EVENT_PASTE);
		return true;
	}
	return false;
}

void Win32Core::checkEvents() {
	lockMutex(eventMutex);
	Win32Event event;
	for(int i=0; i < win32Events.size(); i++) {
		event = win32Events[i];
		switch(event.eventGroup) {
			case Win32Event::INPUT_EVENT:
				switch(event.eventCode) {
					case InputEvent::EVENT_TOUCHES_BEGAN:
						input->touchesBegan(event.touch, event.touches, getTicks());
					break;
					case InputEvent::EVENT_TOUCHES_ENDED:
						input->touchesEnded(event.touch, event.touches, getTicks());
					break;
					case InputEvent::EVENT_TOUCHES_MOVED:
						input->touchesMoved(event.touch, event.touches, getTicks());
					break;
					case InputEvent::EVENT_MOUSEMOVE:
						input->setDeltaPosition(event.mouseX - lastMouseX , event.mouseY - lastMouseY);										
						lastMouseX = event.mouseX;
						lastMouseY = event.mouseY;
						input->setMousePosition(event.mouseX, event.mouseY, getTicks());						
					break;
					case InputEvent::EVENT_MOUSEDOWN:
							input->setMouseButtonState(event.mouseButton, true, getTicks());						
					break;
					case InputEvent::EVENT_MOUSEUP:
							input->setMouseButtonState(event.mouseButton, false, getTicks());
					break;
					case InputEvent::EVENT_MOUSEWHEEL_UP:
						input->mouseWheelUp(getTicks());
					break;
					case InputEvent::EVENT_MOUSEWHEEL_DOWN:
						input->mouseWheelDown(getTicks());						
					break;	
					case InputEvent::EVENT_KEYDOWN:
						if(!checkSpecialKeyEvents((event.keyCode))) {
							input->setKeyState(event.keyCode, (char)event.unicodeChar, true, getTicks());
						}
					break;
					case InputEvent::EVENT_KEYUP:
						input->setKeyState(event.keyCode, (char)event.unicodeChar, false, getTicks());
					break;						
				}
			break;
		}
	}
	win32Events.clear();	
	unlockMutex(eventMutex);		
}

void Win32Core::handleAxisChange(GamepadDeviceEntry * device, int axisIndex, DWORD value) {
	if (axisIndex < 0 || axisIndex >= (int) device->numAxes) {
		return;
	}	
	Gamepad_devicePrivate *devicePrivate = device->privateData;
	float floatVal = (value - devicePrivate->axisRanges[axisIndex][0]) / (float) (devicePrivate->axisRanges[axisIndex][1] - devicePrivate->axisRanges[axisIndex][0]) * 2.0f - 1.0f;
	input->joystickAxisMoved(axisIndex, floatVal, device->deviceID);	
}

void Win32Core::handleButtonChange(GamepadDeviceEntry * device, DWORD lastValue, DWORD value) {
	Gamepad_devicePrivate *devicePrivate = device->privateData;
	unsigned int buttonIndex;	
	for (buttonIndex = 0; buttonIndex < device->numButtons; buttonIndex++) {
		if ((lastValue ^ value) & (1 << buttonIndex)) {
			if(!!(value & (1 << buttonIndex))) {
				input->joystickButtonDown(buttonIndex, device->deviceID);
			} else {
				input->joystickButtonUp(buttonIndex, device->deviceID);
			}
		}
	}
}

static void povToXY(DWORD pov, int * outX, int * outY) {
	if (pov == JOY_POVCENTERED) {
		*outX = *outY = 0;
		
	} else {
		if (pov > JOY_POVFORWARD && pov < JOY_POVBACKWARD) {
			*outX = 1;
			
		} else if (pov > JOY_POVBACKWARD) {
			*outX = -1;
			
		} else {
			*outX = 0;
		}
		
		if (pov > JOY_POVLEFT || pov < JOY_POVRIGHT) {
			*outY = -1;
			
		} else if (pov > JOY_POVRIGHT && pov < JOY_POVLEFT) {
			*outY = 1;
			
		} else {
			*outY = 0;
		}
	}
}

void Win32Core::handlePOVChange(GamepadDeviceEntry * device, DWORD lastValue, DWORD value) {
	
	Gamepad_devicePrivate *devicePrivate = device->privateData;
	
	int lastX, lastY, newX, newY;

	if (devicePrivate->povXAxisIndex == -1 || devicePrivate->povYAxisIndex == -1) {
		return;
	}
	
	povToXY(lastValue, &lastX, &lastY);
	povToXY(value, &newX, &newY);
	
	if (newX != lastX) {
		input->joystickAxisMoved(devicePrivate->povXAxisIndex, newX, device->deviceID);
	}

	if (newY != lastY) {
		input->joystickAxisMoved(devicePrivate->povYAxisIndex, newY, device->deviceID);
	}
}


void Win32Core::Gamepad_processEvents() {

	if(getTicks() > lastGamepadDetect + 3000) {
			detectGamepads();
	}

	unsigned int deviceIndex;
	JOYINFOEX info;
	MMRESULT result;
	GamepadDeviceEntry * device;
	Gamepad_devicePrivate * devicePrivate;
	
	for (deviceIndex = 0; deviceIndex < gamepads.size(); deviceIndex++) {
		device = gamepads[deviceIndex];
		devicePrivate = device->privateData;
		
		info.dwSize = sizeof(info);
		info.dwFlags = JOY_RETURNALL;
		result = joyGetPosEx(devicePrivate->joystickID, &info);
		if (result == JOYERR_UNPLUGGED) {

			input->removeJoystick(device->deviceID);
			gamepads.erase(gamepads.begin() + deviceIndex);
			
		} else if (result == JOYERR_NOERROR) {
			if (info.dwXpos != devicePrivate->lastState.dwXpos) {
				handleAxisChange(device, devicePrivate->xAxisIndex, info.dwXpos);
			}
			if (info.dwYpos != devicePrivate->lastState.dwYpos) {
				handleAxisChange(device, devicePrivate->yAxisIndex, info.dwYpos);
			}
			if (info.dwZpos != devicePrivate->lastState.dwZpos) {
				handleAxisChange(device, devicePrivate->zAxisIndex, info.dwZpos);
			}
			if (info.dwRpos != devicePrivate->lastState.dwRpos) {
				handleAxisChange(device, devicePrivate->rAxisIndex, info.dwRpos);
			}
			if (info.dwUpos != devicePrivate->lastState.dwUpos) {
				handleAxisChange(device, devicePrivate->uAxisIndex, info.dwUpos);
			}
			if (info.dwVpos != devicePrivate->lastState.dwVpos) {
				handleAxisChange(device, devicePrivate->vAxisIndex, info.dwVpos);
			}
			if (info.dwPOV != devicePrivate->lastState.dwPOV) {
				handlePOVChange(device, devicePrivate->lastState.dwPOV, info.dwPOV);
			}
			if (info.dwButtons != devicePrivate->lastState.dwButtons) {
				handleButtonChange(device, devicePrivate->lastState.dwButtons, info.dwButtons);
			}
			devicePrivate->lastState = info;
		}
	}
}

void Win32Core::detectGamepads() {

	lastGamepadDetect = getTicks();

	unsigned int numPadsSupported;
	unsigned int deviceIndex, deviceIndex2;
	JOYINFOEX info;
	JOYCAPS caps;
	bool duplicate;
	Gamepad_devicePrivate * deviceRecordPrivate;
	UINT joystickID;
	int axisIndex;
	
	numPadsSupported = joyGetNumDevs();
	for (deviceIndex = 0; deviceIndex < numPadsSupported; deviceIndex++) {
		info.dwSize = sizeof(info);
		info.dwFlags = JOY_RETURNALL;
		joystickID = JOYSTICKID1 + deviceIndex;
		if (joyGetPosEx(joystickID, &info) == JOYERR_NOERROR &&
		    joyGetDevCaps(joystickID, &caps, sizeof(JOYCAPS)) == JOYERR_NOERROR) {
			
			duplicate = false;
			for (deviceIndex2 = 0; deviceIndex2 < gamepads.size(); deviceIndex2++) {
				if (((Gamepad_devicePrivate *) gamepads[deviceIndex2]->privateData)->joystickID == joystickID) {
					duplicate = true;
					break;
				}
			}
			if (duplicate) {
				continue;
			}
			
			GamepadDeviceEntry *deviceRecord = new GamepadDeviceEntry();
			deviceRecord->deviceID = nextDeviceID++;
//			deviceRecord->description = getDeviceDescription(joystickID, caps);
//			deviceRecord->vendorID = caps.wMid;
//			deviceRecord->productID = caps.wPid;
			deviceRecord->numAxes = caps.wNumAxes + ((caps.wCaps & JOYCAPS_HASPOV) ? 2 : 0);
			deviceRecord->numButtons = caps.wNumButtons;
//			deviceRecord->axisStates = calloc(sizeof(float), deviceRecord->numAxes);
//			deviceRecord->buttonStates = calloc(sizeof(bool), deviceRecord->numButtons);
//			deviceRecord->eventDispatcher = EventDispatcher_create(deviceRecord);
//			devices = realloc(devices, sizeof(struct Gamepad_device *) * (numDevices + 1));
			gamepads.push_back(deviceRecord);
			
			deviceRecordPrivate = new Gamepad_devicePrivate();
			deviceRecordPrivate->joystickID = joystickID;
			deviceRecordPrivate->lastState = info;
			
			deviceRecordPrivate->xAxisIndex = 0;
			deviceRecordPrivate->yAxisIndex = 1;
			axisIndex = 2;
			deviceRecordPrivate->zAxisIndex = (caps.wCaps & JOYCAPS_HASZ) ? axisIndex++ : -1;
			deviceRecordPrivate->rAxisIndex = (caps.wCaps & JOYCAPS_HASR) ? axisIndex++ : -1;
			deviceRecordPrivate->uAxisIndex = (caps.wCaps & JOYCAPS_HASU) ? axisIndex++ : -1;
			deviceRecordPrivate->vAxisIndex = (caps.wCaps & JOYCAPS_HASV) ? axisIndex++ : -1;
			
			deviceRecordPrivate->axisRanges = (UINT (*)[2]) malloc(sizeof(UINT[2]) * axisIndex);
			deviceRecordPrivate->axisRanges[0][0] = caps.wXmin;
			deviceRecordPrivate->axisRanges[0][1] = caps.wXmax;
			deviceRecordPrivate->axisRanges[1][0] = caps.wYmin;
			deviceRecordPrivate->axisRanges[1][1] = caps.wYmax;
			if (deviceRecordPrivate->zAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->zAxisIndex][0] = caps.wZmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->zAxisIndex][1] = caps.wZmax;
			}
			if (deviceRecordPrivate->rAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->rAxisIndex][0] = caps.wRmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->rAxisIndex][1] = caps.wRmax;
			}
			if (deviceRecordPrivate->uAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->uAxisIndex][0] = caps.wUmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->uAxisIndex][1] = caps.wUmax;
			}
			if (deviceRecordPrivate->vAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->vAxisIndex][0] = caps.wVmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->vAxisIndex][1] = caps.wVmax;
			}
			
			deviceRecordPrivate->povXAxisIndex = (caps.wCaps & JOYCAPS_HASPOV) ? axisIndex++ : -1;
			deviceRecordPrivate->povYAxisIndex = (caps.wCaps & JOYCAPS_HASPOV) ? axisIndex++ : -1;
			
			deviceRecord->privateData = deviceRecordPrivate;
			
			input->addJoystick(deviceRecord->deviceID);
		}
	}
}

void Win32Core::initGamepad() {
	nextDeviceID = 0;
	detectGamepads();
}

void Win32Core::shutdownGamepad() {

}

void Win32Core::initTouch() {
#ifdef NO_TOUCH_API
	hasMultiTouch = false;
#else
	// Check for windows multitouch support at runtime
	// This could be done easily during preprocessing but would require building
	// multiple releases of polycode for both winxp/vista and win7
	GetTouchInputInfoFunc = (GetTouchInputInfoType) GetProcAddress(GetModuleHandle(TEXT("user32")), "GetTouchInputInfo");
	
	// If the above multitouch functions were found, then set a flag so we don't
	// have to check again later
	hasMultiTouch = ( GetTouchInputInfoFunc == NULL ) ? false : true;

	if(hasMultiTouch) {
			RegisterTouchWindow(hWnd, 0);
	}
#endif
}


DWORD WINAPI Win32LaunchThread(LPVOID data) {
	Threaded *threaded = (Threaded*)data;
	threaded->runThread();
	return 1;
}


void Win32Core::createThread(Threaded *target) {
	DWORD dwGenericThread; 
	HANDLE handle = CreateThread(NULL,0,Win32LaunchThread,target,0,&dwGenericThread);
}

void Win32Core::lockMutex(CoreMutex *mutex) {	
	WaitForSingleObject(((Win32Mutex*)mutex)->winMutex,INFINITE);
}

void Win32Core::unlockMutex(CoreMutex *mutex) {
	ReleaseMutex(((Win32Mutex*)mutex)->winMutex);
}

void Win32Core::platformSleep(int msecs) {
	Sleep(msecs);
}

CoreMutex *Win32Core::createMutex() {
	Win32Mutex *newMutex = new Win32Mutex();
	newMutex->winMutex = CreateMutex(  NULL, FALSE, NULL);   
	return newMutex;
}
		
std::vector<Polycode::Rectangle> Win32Core::getVideoModes() {
	std::vector<Polycode::Rectangle> retVector;

	return retVector;
}
	

String Win32Core::executeExternalCommand(String command,  String args, String inDirectory) {
	String execInDirectory = inDirectory;
	if(inDirectory == "") {
		execInDirectory = defaultWorkingDirectory;
	}

	SHELLEXECUTEINFO lpExecInfo;
      lpExecInfo.cbSize  = sizeof(SHELLEXECUTEINFO);
      lpExecInfo.lpFile = command.getWDataWithEncoding(String::ENCODING_UTF8);
	lpExecInfo.fMask=SEE_MASK_DOENVSUBST|SEE_MASK_NOCLOSEPROCESS ;     
      lpExecInfo.hwnd = NULL;  
      lpExecInfo.lpVerb = L"open"; // to open  program
      lpExecInfo.lpParameters =  args.getWDataWithEncoding(String::ENCODING_UTF8); //  file name as an argument
      lpExecInfo.lpDirectory = execInDirectory.getWDataWithEncoding(String::ENCODING_UTF8);   
      lpExecInfo.nShow = SW_SHOW ;  // show command prompt with normal window size 
      lpExecInfo.hInstApp = (HINSTANCE) SE_ERR_DDEFAIL ;   //WINSHELLAPI BOOL WINAPI result;
      ShellExecuteEx(&lpExecInfo);
    
 
      //wait until a file is finished printing
      if(lpExecInfo.hProcess !=NULL)
      {
        ::WaitForSingleObject(lpExecInfo.hProcess, INFINITE);
        ::CloseHandle(lpExecInfo.hProcess);
      }

	  return "";
}

String Win32Core::openFolderPicker()  {
	TCHAR szDir[2048];
	BROWSEINFO bInfo;
	bInfo.hwndOwner = hWnd;
	bInfo.pidlRoot = NULL; 
	bInfo.pszDisplayName = szDir;
	bInfo.lpszTitle = L"Choose a folder";
	bInfo.ulFlags = BIF_USENEWUI;
	bInfo.lpfn = NULL;
	bInfo.lParam = 0;
	bInfo.iImage = -1;

	LPITEMIDLIST lpItem = SHBrowseForFolder( &bInfo);
	if( lpItem != NULL ) {
		SHGetPathFromIDList(lpItem, szDir );
		return String(szDir);
	}
	return "";
}

std::vector<String> Win32Core::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	OPENFILENAME ofn;
	wchar_t fBuffer[2048];

	wchar_t filterString[2048];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof ( ofn );
	ofn.hwndOwner = hWnd ;
	ofn.lpstrFile = fBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof( fBuffer );

	if(extensions.size() > 0) {
		int offset = 0;
		for(int i =0; i < extensions.size(); i++) {
		//	filterString += extensions[i].description+"\0*."+extensions[i].extension+"\0";
			memcpy(filterString+offset, extensions[i].description.getWDataWithEncoding(String::ENCODING_UTF8), extensions[i].description.length() * sizeof(wchar_t));
			offset += extensions[i].description.length();
			filterString[offset] = '\0';
			offset++;
			filterString[offset] = '*';
			offset++;
			filterString[offset] = '.';
			offset++;
			memcpy(filterString+offset, extensions[i].extension.getWDataWithEncoding(String::ENCODING_UTF8), extensions[i].extension.length() * sizeof(wchar_t));
			offset += extensions[i].extension.length();
			filterString[offset] = '\0';
			offset++;
		}
		filterString[offset] = '\0';
		ofn.lpstrFilter = filterString;

		ofn.nFilterIndex = 1;
	} else {
		ofn.lpstrFilter = NULL;
	}

	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir=NULL;

	if(allowMultiple) {
		ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER;
	} else {
		ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_EXPLORER;
	}

	std::vector<String> retVec;

	if(GetOpenFileName(&ofn)) {
		if(allowMultiple) {

		} else {
			retVec.push_back(String(fBuffer));
		}
	}

	SetCurrentDirectory(defaultWorkingDirectory.getWDataWithEncoding(String::ENCODING_UTF8));


	for(int i=0; i < retVec.size(); i++) {
		retVec[i] = retVec[i].replace("\\", "/");
	}
	return retVec;
}

void Win32Core::createFolder(const String& folderPath) {
	String path = folderPath;
	CreateDirectory(path.getWDataWithEncoding(String::ENCODING_UTF8), NULL);		
}

void Win32Core::openURL(String url) {
	ShellExecute(NULL, L"open", url.getWDataWithEncoding(String::ENCODING_UTF8), NULL, NULL, SW_SHOWNORMAL);
}

String error_to_string(const DWORD a_error_code)
{
    // Get the last windows error message.
    wchar_t msg_buf[1025] = { 0 };

    // Get the error message for our os code.
    if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
                      0,
                      a_error_code,
                      0,
                      msg_buf,
                      sizeof(msg_buf) - 1,
                      0))
    {
     


        return String(msg_buf);
    }

    return String("Failed to get error message");
}
						
void Win32Core::copyDiskItem(const String& itemPath, const String& destItemPath) {
	SHFILEOPSTRUCT op;
	ZeroMemory(&op, sizeof(SHFILEOPSTRUCT));

	String fromPath = itemPath.replace("/", "\\");
	String toPath =destItemPath.replace("/", "\\");

	fromPath.append('\0');
	toPath.append('\0');

	printf("Copying %s to %s\n", fromPath.c_str(), toPath.c_str());

	op.hwnd = hWnd;
	op.wFunc = FO_COPY;
	op.pFrom = fromPath.getWDataWithEncoding(String::ENCODING_UTF8);
	op.pTo = toPath.getWDataWithEncoding(String::ENCODING_UTF8);
	op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	int ret = SHFileOperation(&op);
	if(ret != 0) {
		String err = error_to_string(ret);
		printf("COPY ERROR: %s\n", err.c_str());
	}
}

void Win32Core::moveDiskItem(const String& itemPath, const String& destItemPath) {
	SHFILEOPSTRUCT op;
	ZeroMemory(&op, sizeof(SHFILEOPSTRUCT));

	String fromPath = itemPath.replace("/", "\\");
	String toPath =destItemPath.replace("/", "\\");

	fromPath.append('\0');
	toPath.append('\0');

	printf("Moving %s to %s\n", fromPath.c_str(), toPath.c_str());

	op.hwnd = hWnd;
	op.wFunc = FO_MOVE;
	op.pFrom = fromPath.getWDataWithEncoding(String::ENCODING_UTF8);
	op.pTo = toPath.getWDataWithEncoding(String::ENCODING_UTF8);
	op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	int ret = SHFileOperation(&op);
	if(ret != 0) {
		String err = error_to_string(ret);
		printf("MOVE ERROR: %s\n", err.c_str());
	}
}

void Win32Core::removeDiskItem(const String& itemPath) {
	SHFILEOPSTRUCT op;
	ZeroMemory(&op, sizeof(SHFILEOPSTRUCT));

	String fromPath = itemPath.replace("/", "\\");
	fromPath.append('\0');

	op.hwnd = hWnd;
	op.wFunc = FO_DELETE;
	op.pFrom = fromPath.getWDataWithEncoding(String::ENCODING_UTF8);
	op.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	int ret = SHFileOperation(&op);
	if(ret != 0) {
		String err = error_to_string(ret);
		printf("COPY ERROR: %s\n", err.c_str());
	}
}

void Win32Core::setCursor(int cursorType) {

	HCURSOR cursor;
	switch(cursorType) {
		case CURSOR_ARROW:
			cursor = LoadCursor(NULL, IDC_ARROW);
		break;
		case CURSOR_TEXT:
			cursor = LoadCursor(NULL, IDC_IBEAM);
		break;
		case CURSOR_POINTER:
			cursor = LoadCursor(NULL, IDC_HAND);
		break;
		case CURSOR_CROSSHAIR:
			cursor = LoadCursor(NULL, IDC_CROSS);
		break;
		case CURSOR_RESIZE_LEFT_RIGHT:
			cursor = LoadCursor(NULL, IDC_SIZEWE);
		break;
		case CURSOR_RESIZE_UP_DOWN:
			cursor = LoadCursor(NULL, IDC_SIZENS);
		break;
		case CURSOR_OPEN_HAND:
			cursor = LoadCursor(NULL, IDC_SIZEALL);
		break;
		default:
			cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	}

	SetCursor(cursor);
	SetClassLongPtr(hWnd, GCLP_HCURSOR, (DWORD)cursor);
}

void  Win32Core::copyStringToClipboard(const String& str) {
	String _tmp = str;
	std::wstring wstr = _tmp.getWDataWithEncoding(String::ENCODING_UTF8);

	const size_t len = ((wstr.size()+1) * sizeof(wchar_t));
	HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), (char*)wstr.c_str(), len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
}

String Win32Core::getClipboardString() {
	OpenClipboard(0);
	HANDLE clip0 = GetClipboardData(CF_UNICODETEXT); 
	HANDLE h= GlobalLock(clip0); 
	wchar_t* c = (wchar_t*) clip0;
	String retString = String(c);
	GlobalUnlock(clip0);
	return retString;
}
