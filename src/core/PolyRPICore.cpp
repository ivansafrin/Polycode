
/*
Copyright (C) 2015 by Ivan Safrin

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

#include "polycode/core/PolyRPICore.h"
#include "polycode/core/PolyBasicFileProvider.h"
#include "polycode/core/PolyOpenGLGraphicsInterface.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace Polycode;

void RPICoreMutex::lock() {
    pthread_mutex_lock(&pMutex);    
}

void RPICoreMutex::unlock() {
    pthread_mutex_unlock(&pMutex);
}


RPICore::RPICore(PolycodeView *view, int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex, bool retinaSupport) 
	: Core(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, frameRate, monitorIndex) {

	bcm_host_init();

	fileProviders.push_back(new BasicFileProvider());
	renderer = new Renderer();
	renderer->setBackingResolutionScale(1.0, 1.0);
	graphicsInterface = new OpenGLGraphicsInterface();
	renderer->setGraphicsInterface(this, graphicsInterface);
	services->setRenderer(renderer);
	setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
	//services->getSoundManager()->setAudioInterface(new XAudio2AudioInterface());
	eventMutex = createMutex();
}

RPICore::~RPICore() {

}

void RPICore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, xRes, yRes));
	renderer->endFrame();
}


void RPICore::checkEvents() {

	eventMutex->lock();

	RPIEvent event;
	for (int i = 0; i < systemInputEvents.size(); i++) {
		event = systemInputEvents[i];
		switch (event.eventGroup) {
		case RPIEvent::INPUT_EVENT:
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
		case RPIEvent::SYSTEM_FOCUS_EVENT:
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

bool RPICore::systemUpdate() {
	if (!running) {
		return false;
	}
	doSleep();
	updateCore();

	checkEvents();
	return running;
}

void RPICore::setCursor(int cursorType) {

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


void RPICore::createThread(Threaded * target) {
	Core::createThread(target);
	pthread_t thread;
	pthread_create( &thread, NULL, ManagedThreadFunc, (void*)target);
}

CoreMutex *RPICore::createMutex() {
	RPICoreMutex *mutex = new RPICoreMutex();
	pthread_mutex_init(&mutex->pMutex, NULL);
	return mutex;
}

void RPICore::copyStringToClipboard(const String& str) {

}

String RPICore::getClipboardString() {
	return "";
}

void RPICore::createFolder(const String& folderPath) {

}

void RPICore::copyDiskItem(const String& itemPath, const String& destItemPath) {

}

void RPICore::moveDiskItem(const String& itemPath, const String& destItemPath) {

}

void RPICore::removeDiskItem(const String& itemPath) {

}

String RPICore::openFolderPicker() {
	return "";
}

std::vector<String> RPICore::openFilePicker(std::vector<CoreFileExtension> extensions, bool allowMultiple) {
	std::vector<String> ret;
	return ret;
}

String RPICore::saveFilePicker(std::vector<CoreFileExtension> extensions) {
	return "";
}

void RPICore::handleVideoModeChange(VideoModeChangeInfo *modeInfo) {

	int32_t success = 0;
	EGLBoolean result;
	EGLint num_config;

	this->xRes = modeInfo->xRes;
	this->yRes = modeInfo->yRes;
	this->fullScreen = modeInfo->fullScreen;
	this->aaLevel = modeInfo->aaLevel;
	this->vSync = modeInfo->vSync;

	static EGL_DISPMANX_WINDOW_T nativewindow;

	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;

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

	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	result = eglInitialize(display, NULL, NULL);
	result = eglChooseConfig(display, attribute_list, &config, 1, &num_config);
	assert(EGL_FALSE != result);
	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(EGL_FALSE != result);

	context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attributes);
	assert(context!=EGL_NO_CONTEXT);

	uint32_t xr;
	uint32_t yr;
	success = graphics_get_display_size(0 /* LCD */, &xr, &yr);

	xRes = xr;
	yRes = yr;
	
	assert( success >= 0 );


	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = xRes;
	dst_rect.height = yRes;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = xRes << 16;
	src_rect.height = yRes << 16;		

	dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
	dispman_update = vc_dispmanx_update_start( 0 );

	dispman_element = 
	vc_dispmanx_element_add(dispman_update, dispman_display,
				0/*layer*/, &dst_rect, 0/*src*/,
				&src_rect, DISPMANX_PROTECTION_NONE, 
				0 /*alpha*/, 0/*clamp*/, (DISPMANX_TRANSFORM_T)0/*transform*/);

	nativewindow.element = dispman_element;
	nativewindow.width = xRes;
	nativewindow.height = yRes;
	vc_dispmanx_update_submit_sync( dispman_update );

	surface = eglCreateWindowSurface( display, config, &nativewindow, NULL );
	assert(surface != EGL_NO_SURFACE);

	// connect the context to the surface
	result = eglMakeCurrent(display, surface, surface, context);
	assert(EGL_FALSE != result);

}

void RPICore::flushRenderContext() {
	glFlush();
	eglSwapBuffers(display, surface);
}

void RPICore::openURL(String url) {

}

unsigned int RPICore::getTicks() {
	return 0;
}

String RPICore::executeExternalCommand(String command, String args, String inDirectory) {
	return "";
}

bool RPICore::systemParseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {
	
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

void RPICore::handleSystemEvent(RPIEvent systemEvent) {
	eventMutex->lock();
	systemInputEvents.push_back(systemEvent);
	eventMutex->unlock();
}

void Core::getScreenInfo(int *width, int *height, int *hz) {

}

void RPICore::setDeviceSize(Number x, Number y) {
	deviceWidth = x;
	deviceHeight = y;

	renderer->setBackingResolutionScale(xRes/deviceWidth, yRes/deviceHeight);
}

Number RPICore::getBackingXRes() {
	return deviceWidth;
}

Number RPICore::getBackingYRes() {
	return deviceHeight;
}
