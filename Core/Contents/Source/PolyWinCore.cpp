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

#include "PolyGLHeaders.h"
#include "PolyWinCore.h"
#include "PolyCoreInput.h"
#include "PolyCoreServices.h"
#include "PolyInputEvent.h"
#include "PolyGLRenderer.h"
#include "PolyGLSLShaderModule.h"
#include "PolyLogger.h"
#include "PolyThreaded.h"

#include <GL/gl.h>
#include <GL/glext.h>
#ifndef _MINGW
#include <GL/wglext.h>
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

Win32Core::Win32Core(PolycodeViewBase *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate) 
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate) {

	hWnd = *((HWND*)view->windowData);
	core = this;
	initKeymap();

	hDC = NULL;
	hRC = NULL;
	PixelFormat = 0;
	
	lastMouseX = -1;
	lastMouseY = -1;

	eventMutex = createMutex();

	isFullScreen = fullScreen;

	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);

	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
		
//	WSADATA WsaData;
///	if(WSAStartup( MAKEWORD(2,2), &WsaData ) != NO_ERROR ){
//		Logger::log("Error initializing sockets!\n");
//	}

	((OpenGLRenderer*)renderer)->initOSSpecific();

	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
}

Win32Core::~Win32Core() {
	destroyContext();
}

void Win32Core::enableMouse(bool newval) {
	ShowCursor(newval);	
}

unsigned int Win32Core::getTicks() {
	return GetTickCount();
}

bool Win32Core::Update() {
	if(!running)
		return false;

	checkEvents();

	renderer->BeginRender();
	updateCore();
	renderer->EndRender();
	
	SwapBuffers(hDC);
	doSleep();
	return running;
}

void Win32Core::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel) {

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
		if(isFullScreen) {
			ChangeDisplaySettings(NULL,0);		
		}
	//	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPED|WS_SYSMENU);
	//	ShowWindow(hWnd, SW_SHOW);
		ClientResize(hWnd, xRes, yRes);
	}


	isFullScreen = fullScreen;

	initContext(false, 0);

	if(aaLevel > 0) {
		initMultisample(aaLevel);
	}

	renderer->Resize(xRes, yRes);
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
	bool valid;
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

PolyKEY Win32Core::mapKey(LPARAM lParam, WPARAM wParam) {
		switch (wParam) {
				case VK_CONTROL:
					if ( lParam&EXTENDED_KEYMASK )
						wParam = VK_RCONTROL;
					else
						wParam = VK_LCONTROL;
				break;
				case 33:
					if ( lParam&EXTENDED_KEYMASK )
						wParam = VK_RMENU;
					else
						wParam = VK_LMENU;
					break;
			}

	return keyMap[(unsigned int)wParam];
}

void Win32Core::handleKeyDown(LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYDOWN;
	newEvent.keyCode = mapKey(lParam, wParam);
	newEvent.unicodeChar = ' ';
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

void Win32Core::handleKeyUp(LPARAM lParam, WPARAM wParam) {
	lockMutex(eventMutex);
	Win32Event newEvent;
	newEvent.eventGroup = Win32Event::INPUT_EVENT;
	newEvent.eventCode = InputEvent::EVENT_KEYUP;
	newEvent.keyCode = mapKey(lParam, wParam);
	newEvent.unicodeChar = ' ';
	win32Events.push_back(newEvent);
	unlockMutex(eventMutex);
}

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

void Win32Core::checkEvents() {
	lockMutex(eventMutex);
	Win32Event event;
	for(int i=0; i < win32Events.size(); i++) {
		event = win32Events[i];
		switch(event.eventGroup) {
			case Win32Event::INPUT_EVENT:
				switch(event.eventCode) {
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
					case InputEvent::EVENT_KEYDOWN:
						input->setKeyState(event.keyCode, (char)event.unicodeChar, true, getTicks());
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
	
