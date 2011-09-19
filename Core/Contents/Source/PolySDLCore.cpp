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

#include "PolySDLCore.h"
#include "PolycodeView.h"
#include "PolyCoreServices.h"
#include "PolyCoreInput.h"
#include "PolyMaterialManager.h"
#include "PolyThreaded.h"

#include "PolyGLRenderer.h"
#include "PolyGLSLShaderModule.h"
#include "PolyRectangle.h"

#include <SDL/SDL.h>
#include <iostream>

using namespace Polycode;
using std::vector;

long getThreadID() {
	return (long)pthread_self();
}

SDLCore::SDLCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate) : Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate) {

	String *windowTitle = (String*)view->windowData;

	putenv("SDL_VIDEO_CENTERED=1");

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
	}
	
	renderer = new OpenGLRenderer();
	services->setRenderer(renderer);

	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel);
	SDL_WM_SetCaption(windowTitle->c_str(), windowTitle->c_str());
	
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	
	((OpenGLRenderer*)renderer)->initOSSpecific();
	CoreServices::getInstance()->installModule(new GLSLShaderModule());	
}

void SDLCore::setVideoMode(int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel) {
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24);	
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);			
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,   8);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,  8);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
	
	if(aaLevel > 0) {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, aaLevel); //0, 2, 4	
	} else {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 0);
	}
	
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
	
	if(fullScreen) {
		if( SDL_SetVideoMode(xRes, yRes, 0, SDL_OPENGL|SDL_FULLSCREEN) == NULL ) {
		}	
	} else {
		if( SDL_SetVideoMode(xRes, yRes, 0, SDL_OPENGL) == NULL ) {
		}
	}
	
	renderer->Resize(xRes, yRes);
	CoreServices::getInstance()->getMaterialManager()->reloadProgramsAndTextures();
}

vector<Polycode::Rectangle> SDLCore::getVideoModes() {
	vector<Polycode::Rectangle> retVector;
	
	SDL_Rect **modes;
	modes=SDL_ListModes(NULL, SDL_FULLSCREEN);
	for(int i=0;modes[i];++i) {
		Rectangle res;
		res.w = modes[i]->w;
		res.h = modes[i]->h;
		retVector.push_back(res);
	}	
	
	return retVector;
}

SDLCore::~SDLCore() {
	SDL_Quit();
}

int SDLThreadFunc(void *data) {
	Threaded *target = (Threaded*)data;
	target->runThread();
	return 1;
}

void SDLCore::createThread(Threaded *target) {
	SDL_CreateThread(SDLThreadFunc, (void*)target);
}

unsigned int SDLCore::getTicks() {
	return SDL_GetTicks();
}

void SDLCore::enableMouse(bool newval) {
	if(newval) {
		SDL_ShowCursor(1);
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	} else {
		SDL_ShowCursor(0);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	}
	Core::enableMouse(newval);
}
	
bool SDLCore::Update() {
	if(!running)
		return false;
	
	renderer->BeginRender();
	updateCore();
	renderer->EndRender();
	SDL_GL_SwapBuffers();
	
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
				break;
				case SDL_JOYBUTTONDOWN:
//					input->setKeyState((PolyKEY)(event.key.keysym.sym), true);
				break;
				case SDL_KEYDOWN:
					input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.unicode, true, getTicks());
				break;
				case SDL_KEYUP:
					input->setKeyState((PolyKEY)(event.key.keysym.sym), (char)event.key.keysym.unicode, false, getTicks());
				break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_WHEELUP) {
						input->mouseWheelUp(getTicks());
					} else if(event.button.button == SDL_BUTTON_WHEELDOWN) {
						input->mouseWheelDown(getTicks());
					} else {
						input->setMouseButtonState(CoreInput::MOUSE_BUTTON1, true, getTicks());
					}
				break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_WHEELUP || event.button.button == SDL_BUTTON_WHEELDOWN) {						
					} else {
						input->setMouseButtonState(CoreInput::MOUSE_BUTTON1, false, getTicks());
					}
				break;
				case SDL_MOUSEMOTION:
					input->setDeltaPosition(event.motion.xrel, event.motion.yrel);					
					input->setMousePosition(event.motion.x, event.motion.y, getTicks());
				break;
				default:
					break;
			}
		}
	doSleep();	
	return running;
}

void SDLCore::setCursor(int cursorType) {

}

void SDLCore::lockMutex(CoreMutex *mutex) {
	SDLCoreMutex *smutex = (SDLCoreMutex*)mutex;
	SDL_mutexP(smutex->pMutex);

}

void SDLCore::unlockMutex(CoreMutex *mutex) {
	SDLCoreMutex *smutex = (SDLCoreMutex*)mutex;
	SDL_mutexV(smutex->pMutex);
}

CoreMutex *SDLCore::createMutex() {
	SDLCoreMutex *mutex = new SDLCoreMutex();
	mutex->pMutex = SDL_CreateMutex();
	return mutex;	
}

void SDLCore::copyStringToClipboard(const String& str) {

}

String SDLCore::getClipboardString() {

}

void SDLCore::createFolder(const String& folderPath) {

}

void SDLCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void SDLCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void SDLCore::removeDiskItem(const String& itemPath) {
}

String SDLCore::openFolderPicker() {

}

vector<String> SDLCore::openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple) {

}

void SDLCore::resizeTo(int xRes, int yRes) {
	renderer->Resize(xRes, yRes);
}

