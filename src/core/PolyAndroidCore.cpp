/*
 Copyright (C) 2016 by Joachim Meyer
 
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

#include "polycode/core/PolyAndroidCore.h"
#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolyAAssetFileProvider.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyOpenSLAudioInterface.h"
#include "polycode/view/android/PolycodeView.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace Polycode;

extern AndroidCore *core;

void AndroidCoreMutex::lock() {
    pthread_mutex_lock(&pMutex);    
}

void AndroidCoreMutex::unlock() {
    pthread_mutex_unlock(&pMutex);
}


AndroidCore::AndroidCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) 
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {
	
	fileProviders.push_back(new AAssetFileProvider(view->native_activity->assetManager));
	
	eventMutex = createMutex();
	eglMutex = createMutex();
	
	renderer = new Renderer();
	renderer->setBackingResolutionScale(1.0, 1.0);
	graphicsInterface = new OpenGLGraphicsInterface();
	renderer->setGraphicsInterface(this, graphicsInterface);
	services->setRenderer(renderer);
	
	context = NULL;
	surface = NULL;
	recreateContext = true;
	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);

	//services->getSoundManager()->setAudioInterface(new OpenSLAudioInterface());
	
	paused = true;
	
	this->view = view;
	core = this;
	
}

AndroidCore::~AndroidCore() {

}

void AndroidCore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, xRes, yRes));
	renderer->endFrame();
}

void AndroidCore::checkEvents() {

	eventMutex->lock();
	
	AndroidEvent event;
	for (int i = 0; i < systemInputEvents.size(); i++) {
		event = systemInputEvents[i];
		switch (event.eventGroup) {
		case AndroidEvent::INPUT_EVENT:
			switch (event.eventCode) {
			case InputEvent::EVENT_MOUSEMOVE:
				input->setDeltaPosition(lastMouseX - event.mouseX, lastMouseY - event.mouseY);
				lastMouseX = event.mouseX;
				lastMouseY = event.mouseY;
				input->setMousePosition(event.mouseX, event.mouseY, getTicks());
				break;
			case InputEvent::EVENT_MOUSEDOWN:
				input->mousePosition.x = event.mouseX;
				input->mousePosition.y = event.mouseY;
				input->setMouseButtonState(event.mouseButton, true, getTicks());
				break;
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				input->mouseWheelUp(getTicks());
				break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				input->mouseWheelDown(getTicks());
				break;
			case InputEvent::EVENT_MOUSEUP:
				input->setMouseButtonState(event.mouseButton, false, getTicks());
				break;
			case InputEvent::EVENT_KEYDOWN:
				if (!checkSpecialKeyEvents(event.keyCode))
					input->setKeyState(event.keyCode, event.unicodeChar, true, getTicks());
				break;
			case InputEvent::EVENT_KEYUP:
				input->setKeyState(event.keyCode, event.unicodeChar, false, getTicks());
				break;
			case InputEvent::EVENT_TOUCHES_BEGAN:
				input->touchesBegan(event.touch, event.touches, getTicks());
				break;
			case InputEvent::EVENT_TOUCHES_ENDED:
				input->touchesEnded(event.touch, event.touches, getTicks());
				break;
			case InputEvent::EVENT_TOUCHES_MOVED:
				input->touchesMoved(event.touch, event.touches, getTicks());
				break;
			}
			break;
		case AndroidEvent::SYSTEM_FOCUS_EVENT:
			switch (event.eventCode) {
			case Core::EVENT_LOST_FOCUS:
				loseFocus();
				break;
			case Core::EVENT_GAINED_FOCUS:
				gainFocus();
				break;
			}
			break;
		}
	}

	systemInputEvents.clear();
	eventMutex->unlock();

}

bool AndroidCore::systemUpdate() {
	if (!running) {
		return false;
	}
	doSleep();

	updateCore();
	checkEvents();

	return running;
}

void AndroidCore::setCursor(int cursorType) {

}

void launchThread(Threaded *target) {
	target->runThread();
	target->scheduledForRemoval = true;
}

void *ManagedThreadFunc(void *data) {
	Threaded *target = static_cast<Threaded*>(data);
	target->runThread();
	target->scheduledForRemoval = true;
	return NULL;
}


void AndroidCore::createThread(Threaded * target) {
	Core::createThread(target);
	pthread_t thread;
	pthread_create( &thread, NULL, ManagedThreadFunc, (void*)target);
}

CoreMutex *AndroidCore::createMutex() {
	AndroidCoreMutex *mutex = new AndroidCoreMutex();
	pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;
}

void AndroidCore::copyStringToClipboard(const String& str) {

}

String AndroidCore::getClipboardString() {
	return "";
}

void AndroidCore::createFolder(const String& folderPath) {

}

void AndroidCore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void AndroidCore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void AndroidCore::removeDiskItem(const String& itemPath) {

}

String AndroidCore::openFolderPicker() {
	return "";
}

std::vector<String> AndroidCore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String AndroidCore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void AndroidCore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {
	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;

	this->xRes = modeInfo->xRes;
	this->yRes = modeInfo->yRes;
	this->fullScreen = modeInfo->fullScreen;
	this->aaLevel = modeInfo->aaLevel;
	this->vSync = modeInfo->vSync;
	this->anisotropyLevel = modeInfo->anisotropyLevel;

	if(!view->native_window){
		return;
	}
	
	if (recreateContext){
		eglMutex->lock();
		static const EGLint attribute_list[] =
		{
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_NONE
		};

		static const EGLint context_attributes[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLConfig config;
		EGLint format;
		
		display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		result = eglInitialize(display, NULL, NULL);
		
		result = eglChooseConfig(display, attribute_list, &config, 1, &num_config);
		assert(EGL_FALSE != result);
		
		if (eglQueryAPI() == EGL_NONE){
			result = eglBindAPI(EGL_OPENGL_ES_API);
			assert(EGL_FALSE != result);
		}
		
		if(!context){
			context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attributes);
			assert(context!=EGL_NO_CONTEXT);
		}
		
		if(surface)
			eglDestroySurface(display, surface);
		
		surface = eglCreateWindowSurface( display, config, view->native_window, NULL );
		assert(surface != EGL_NO_SURFACE);

		// connect the context to the surface
		result = eglMakeCurrent(display, surface, surface, context);
		assert(EGL_FALSE != result);
		Logger::log("EGL Init finished");
		
		recreateContext = false;
		eglMutex->unlock();
	}
}

void AndroidCore::flushRenderContext() {
	glFlush();
	eglSwapBuffers(display, surface);
}

bool AndroidCore::isWindowInitialized(){
// 	Logger::log("isWindowInitialized");
	eglMutex->lock();
// 	Logger::log("locked");
	if (eglGetCurrentContext() == EGL_NO_CONTEXT || recreateContext){
		eglMutex->unlock();
		return false;
	} else {
		eglMutex->unlock();
		return true;
	}
}

CoreMutex* AndroidCore::getEGLMutex(){
	return eglMutex;
}

void AndroidCore::openURL(String url) {

}

unsigned int AndroidCore::getTicks() {
	struct timespec now;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
	return now.tv_sec * 1000000L + now.tv_nsec/1000;
}

String AndroidCore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}

bool AndroidCore::systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {
	
    DIR           *d;
    struct dirent *dir;
    
    d = opendir(pathString.c_str());
    if(d) {
        while ((dir = readdir(d)) != NULL) {
            if(dir->d_name[0] != '.' || (dir->d_name[0] == '.'  && showHidden)) {
                if(dir->d_type == DT_DIR) {
                    targetVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FOLDER));
                } else {
                    targetVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FILE));
                }
            }
        }
        closedir(d);
    }
    return true;
}

void AndroidCore::handleSystemEvent(AndroidEvent systemEvent) {
	eventMutex->lock();
	systemInputEvents.push_back(systemEvent);
	eventMutex->unlock();
}

void Core::getScreenInfo(int *width, int *height, int *hz) {

}

void AndroidCore::setDeviceSize(Number x, Number y) {
	deviceWidth = x;
	deviceHeight = y;

	renderer->setBackingResolutionScale(xRes/deviceWidth, yRes/deviceHeight);
}

Number AndroidCore::getBackingXRes() {
	return deviceWidth;
}

Number AndroidCore::getBackingYRes() {
	return deviceHeight;
}
