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

#include "PolyAGLCore.h"
#include <iostream>

using namespace Polycode;

long getThreadID() {
	return (long)pthread_self();
}

AGLCore::AGLCore(WindowRef window, Polycode::Rectangle *clippingArea, int xRes, int yRes, bool fullScreen,int aaLevel, int frameRate) : Core(xRes, yRes, fullScreen,aaLevel, frameRate) {

	eventMutex = createMutex();
	
	mainWindow = window;
	initTime = mach_absolute_time();	
	
	lockMutex(CoreServices::getRenderMutex());
	
	int numBuffers = 0;	
	if(aaLevel > 0) {
		numBuffers = 1;
	}
	
	AGLPixelFormat pf;
	
	printf("AA: %d\n", aaLevel);
		
	if(aaLevel > 0) {	
		GLint attrib[] = { AGL_RGBA,
		AGL_DEPTH_SIZE, 32,
		AGL_RED_SIZE, 8,
		AGL_GREEN_SIZE, 8,
		AGL_BLUE_SIZE, 8,
		AGL_ALPHA_SIZE, 8,			
		AGL_DOUBLEBUFFER,
		AGL_SAMPLE_BUFFERS_ARB, numBuffers,
		AGL_SAMPLES_ARB, aaLevel,
		AGL_SUPERSAMPLE,
		AGL_NO_RECOVERY,
		AGL_NONE };		
		pf = aglChoosePixelFormat (NULL, 0, attrib);
	} else {
		GLint attrib[] = { AGL_RGBA,
			AGL_DEPTH_SIZE, 32,
			AGL_RED_SIZE, 8,
			AGL_GREEN_SIZE, 8,
			AGL_BLUE_SIZE, 8,
			AGL_ALPHA_SIZE, 8,			
			AGL_DOUBLEBUFFER,
			AGL_SAMPLE_BUFFERS_ARB, 0,
			AGL_SAMPLES_ARB, 0,
			AGL_SUPERSAMPLE,
			AGL_NO_RECOVERY,
		AGL_NONE };		
		pf = aglChoosePixelFormat (NULL, 0, attrib);		
	}

	aglContext = NULL;
	aglContext = aglCreateContext (pf, NULL);

	if (aglContext) {
		aglSetWindowRef(aglContext,window);
		aglSetCurrentContext (NULL);		
		aglSetCurrentContext (aglContext);
	} else {
		Logger::log("ERROR CREATING AGL CONTEXT!\n");
	}
		
	aglDestroyPixelFormat (pf);	
	
	if(clippingArea) {
		const GLint bufferRect[4] = {clippingArea->x, clippingArea->y, clippingArea->w, clippingArea->h};	
		aglSetInteger(aglContext, AGL_BUFFER_RECT, bufferRect);
		aglEnable(aglContext, AGL_BUFFER_RECT);	
	}
	
	renderer = new OpenGLRenderer();

	if(aaLevel > 0) {
		glEnable (GL_MULTISAMPLE_ARB);
		glHint (GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);		
	}
	
	services->setRenderer(renderer);
	renderer->Resize(xRes, yRes);
	
	unlockMutex(CoreServices::getRenderMutex());		
	
//	setVideoMode(xRes, yRes, fullScreen, aaLevel);	
}
				 
void AGLCore::setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel) {
	lockMutex(CoreServices::getRenderMutex());	
	dispatchEvent(new Event(), EVENT_CORE_RESIZE);
	
	aglSetCurrentContext (NULL);		
	aglSetCurrentContext (aglContext);

	const GLint bufferRect[4] = {0, 0, xRes, yRes};	
	aglSetInteger(aglContext, AGL_BUFFER_RECT, bufferRect);
	aglEnable(aglContext, AGL_BUFFER_RECT);		

	if(fullScreen) {
		aglEnable (aglContext, AGL_FS_CAPTURE_SINGLE);		
		aglSetFullScreen(aglContext, xRes, yRes, 0, 0);
	} else {
		
	}
	
	renderer->Resize(xRes, yRes);
	
	if(aaLevel > 0) {
		glEnable (GL_MULTISAMPLE_ARB);
		glHint (GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);		
	}
	
	unlockMutex(CoreServices::getRenderMutex());	

	CoreServices::getInstance()->getMaterialManager()->reloadProgramsAndTextures();
	
}

vector<Poly::Rectangle> AGLCore::getVideoModes() {
	vector<Poly::Rectangle> retVector;
	return retVector;
}

AGLCore::~AGLCore() {
	Logger::log("Destroying AGL core...\n");
	aglDestroyContext(aglContext);
}

void *AGLThreadFunc(void *data) {
	Threaded *target = static_cast<Threaded*>(data);
	target->runThread();
	return NULL;
}

void AGLCore::createThread(Threaded *target) {
	pthread_t thread;
	pthread_create( &thread, NULL, AGLThreadFunc, (void*)target);
}

void AGLCore::lockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_lock(&m->pMutex);	
}

void AGLCore::unlockMutex(CoreMutex *mutex) {
	PosixMutex *m = (PosixMutex*) mutex;
	pthread_mutex_unlock(&m->pMutex);
}

CoreMutex *AGLCore::createMutex() {
	PosixMutex *mutex = new PosixMutex();	
	pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;
}

unsigned int AGLCore::getTicks() {
	uint64_t time = mach_absolute_time();	
	double conversion = 0.0;
	
	mach_timebase_info_data_t info;
	mach_timebase_info( &info );
	conversion = 1e-9 * (double) info.numer / (double) info.denom;	
	
	return (((double)(time - initTime)) * conversion) * 1000.0f;
}

void AGLCore::enableMouse(bool newval) {
	Core::enableMouse(newval);
}

void AGLCore::checkEvents() {
	lockMutex(eventMutex);
	OSXEvent event;
	for(int i=0; i < osxEvents.size(); i++) {
		event = osxEvents[i];
		switch(event.eventGroup) {
			case OSXEvent::INPUT_EVENT:
				switch(event.eventCode) {
					case InputEvent::EVENT_MOUSEMOVE:
						input->setDeltaPosition(lastMouseX - event.mouseX, lastMouseY - event.mouseY);										
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
	osxEvents.clear();	
	unlockMutex(eventMutex);		
}

bool AGLCore::Update() {
	if(!running)
		return false;
		
	lockMutex(CoreServices::getRenderMutex());
	
	checkEvents();
	
//	aglSetCurrentContext(NULL);
//	aglSetCurrentContext(aglContext);
	renderer->BeginRender();
	updateCore();
	renderer->EndRender();

	aglSwapBuffers(aglContext);
//	aglSetCurrentContext(NULL);
	
	unlockMutex(CoreServices::getRenderMutex());
	doSleep();
	
	return running;
}