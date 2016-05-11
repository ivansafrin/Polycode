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
#include "polycode/core/PolyBasicFileProvider.h"
#include "polycode/core/PolyPhysFSFileProvider.h"
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
	fileProviders.push_back(new BasicFileProvider());
	fileProviders.push_back(new PhysFSFileProvider());
	
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
	
	//scale needs to be set now so that labels are scaled correctly	
	if(retinaSupport){
		float scale = 1.0;
		int dens = AConfiguration_getDensity(view->native_config);
		if(dens >=ACONFIGURATION_DENSITY_LOW && dens <= ACONFIGURATION_DENSITY_XXXHIGH){
			scale = dens / ACONFIGURATION_DENSITY_MEDIUM;
		}
		renderer->setBackingResolutionScale(scale, scale);
	}
	
	//DP are the Density Independent Pixels - this is afaik what should be the size this should work with enabled retinaSupport
	setVideoMode(AConfiguration_getScreenWidthDp(view->native_config), AConfiguration_getScreenHeightDp(view->native_config), fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
	
	defaultWorkingDirectory = view->native_activity->internalDataPath;
	userHomeDirectory = view->native_activity->internalDataPath;
	
// 	services->getSoundManager()->setAudioInterface(new OpenSLAudioInterface());
	paused = true;
	
	initKeyMap();
	
	this->view = view;
	core = this;
}

AndroidCore::~AndroidCore() {

}

void AndroidCore::Render() {
	renderer->beginFrame();
	services->Render(Polycode::Rectangle(0, 0, getBackingXRes(), getBackingYRes()));
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
	ALooper_pollAll(0, NULL, NULL, NULL);
	
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
	
	float scale = 1.0;
	if(modeInfo->retinaSupport){
		int dens = AConfiguration_getDensity(view->native_config);
		if(dens >=ACONFIGURATION_DENSITY_LOW && dens <= ACONFIGURATION_DENSITY_XXXHIGH){
			scale = dens / ACONFIGURATION_DENSITY_MEDIUM;
		}
	}
	renderer->setBackingResolutionScale(scale, scale);
	
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
		
		// this works on my Fairphone but not in the Emulator.. and it did work in the Emulator for quite some while.. but now it says: "E/Surface﹕ getSlotFromBufferLocked: unknown buffer:"
		// everything is running without this as well...
// 		if(surface)
// 			eglDestroySurface(display, surface);
		
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
	eglMutex->lock();
// 	Logger::log("locked");
	if (eglGetCurrentContext() == EGL_NO_CONTEXT || recreateContext || !view->isInteractable()){
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
	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec * 1000 + now.tv_nsec/1000000;
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
}

Number AndroidCore::getBackingXRes() {
	return deviceWidth;
}

Number AndroidCore::getBackingYRes() {
	return deviceHeight;
}

void AndroidCore::_setAcceleration(const Vector3 &acceleration) {
    CoreMotionEvent *event = new CoreMotionEvent();
    event->amount = acceleration;
    dispatchEvent(event, Core::EVENT_ACCELEROMETER_MOTION);
}

void AndroidCore::_setGyroRotation(const Vector3 &rotation) {
    CoreMotionEvent *event = new CoreMotionEvent();
    event->amount = rotation;
    dispatchEvent(event, Core::EVENT_GYRO_ROTATION);
}

void AndroidCore::initKeyMap() {
	
	for (int i=0; i<1024; ++i )
		keyMap[i] = KEY_UNKNOWN;

	keyMap[AKEYCODE_BACK] = KEY_BACKSPACE;
	keyMap[AKEYCODE_TAB] = KEY_TAB;
	keyMap[AKEYCODE_CLEAR] = KEY_CLEAR;
	keyMap[AKEYCODE_ENTER] = KEY_RETURN;
	keyMap[AKEYCODE_BREAK] = KEY_PAUSE;
	keyMap[AKEYCODE_ESCAPE] = KEY_ESCAPE;
	keyMap[AKEYCODE_SPACE] = KEY_SPACE;
	keyMap[AKEYCODE_APOSTROPHE] = KEY_QUOTE;
	keyMap[AKEYCODE_COMMA] = KEY_COMMA;
	keyMap[AKEYCODE_MINUS] = KEY_MINUS;
	keyMap[AKEYCODE_PERIOD] = KEY_PERIOD;
	keyMap[AKEYCODE_SLASH] = KEY_SLASH;
	keyMap[AKEYCODE_0] = KEY_0;
	keyMap[AKEYCODE_1] = KEY_1;
	keyMap[AKEYCODE_2] = KEY_2;
	keyMap[AKEYCODE_3] = KEY_3;
	keyMap[AKEYCODE_4] = KEY_4;
	keyMap[AKEYCODE_5] = KEY_5;
	keyMap[AKEYCODE_6] = KEY_6;
	keyMap[AKEYCODE_7] = KEY_7;
	keyMap[AKEYCODE_8] = KEY_8;
	keyMap[AKEYCODE_9] = KEY_9;
	keyMap[AKEYCODE_SEMICOLON] = KEY_SEMICOLON;
	keyMap[AKEYCODE_EQUALS] = KEY_EQUALS;
	keyMap[AKEYCODE_LEFT_BRACKET] = KEY_LEFTBRACKET;
	keyMap[AKEYCODE_BACKSLASH] = KEY_BACKSLASH;
// 	keyMap[AKEYCODE_OEM_102] = KEY_LESS;
	keyMap[AKEYCODE_RIGHT_BRACKET] = KEY_RIGHTBRACKET;
	keyMap[AKEYCODE_GRAVE] = KEY_BACKQUOTE;
	//keyMap[AKEYCODE_BACKTICK] = KEY_BACKQUOTE;
	keyMap[AKEYCODE_A] = KEY_a;
	keyMap[AKEYCODE_B] = KEY_b;
	keyMap[AKEYCODE_C] = KEY_c;
	keyMap[AKEYCODE_D] = KEY_d;
	keyMap[AKEYCODE_E] = KEY_e;
	keyMap[AKEYCODE_F] = KEY_f;
	keyMap[AKEYCODE_G] = KEY_g;
	keyMap[AKEYCODE_H] = KEY_h;
	keyMap[AKEYCODE_I] = KEY_i;
	keyMap[AKEYCODE_J] = KEY_j;
	keyMap[AKEYCODE_K] = KEY_k;
	keyMap[AKEYCODE_L] = KEY_l;
	keyMap[AKEYCODE_M] = KEY_m;
	keyMap[AKEYCODE_N] = KEY_n;
	keyMap[AKEYCODE_O] = KEY_o;
	keyMap[AKEYCODE_P] = KEY_p;
	keyMap[AKEYCODE_Q] = KEY_q;
	keyMap[AKEYCODE_R] = KEY_r;
	keyMap[AKEYCODE_S] = KEY_s;
	keyMap[AKEYCODE_T] = KEY_t;
	keyMap[AKEYCODE_U] = KEY_u;
	keyMap[AKEYCODE_V] = KEY_v;
	keyMap[AKEYCODE_W] = KEY_w;
	keyMap[AKEYCODE_X] = KEY_x;
	keyMap[AKEYCODE_Y] = KEY_y;
	keyMap[AKEYCODE_Z] = KEY_z;
	keyMap[AKEYCODE_DEL] = KEY_DELETE;

	keyMap[AKEYCODE_NUMPAD_0] = KEY_KP0;
	keyMap[AKEYCODE_NUMPAD_1] = KEY_KP1;
	keyMap[AKEYCODE_NUMPAD_2] = KEY_KP2;
	keyMap[AKEYCODE_NUMPAD_3] = KEY_KP3;
	keyMap[AKEYCODE_NUMPAD_4] = KEY_KP4;
	keyMap[AKEYCODE_NUMPAD_5] = KEY_KP5;
	keyMap[AKEYCODE_NUMPAD_6] = KEY_KP6;
	keyMap[AKEYCODE_NUMPAD_7] = KEY_KP7;
	keyMap[AKEYCODE_NUMPAD_8] = KEY_KP8;
	keyMap[AKEYCODE_NUMPAD_9] = KEY_KP9;
	keyMap[AKEYCODE_NUMPAD_DOT] = KEY_KP_PERIOD;
	keyMap[AKEYCODE_NUMPAD_DIVIDE] = KEY_KP_DIVIDE;
	keyMap[AKEYCODE_NUMPAD_MULTIPLY] = KEY_KP_MULTIPLY;
	keyMap[AKEYCODE_NUMPAD_SUBTRACT] = KEY_KP_MINUS;
	keyMap[AKEYCODE_NUMPAD_ADD] = KEY_KP_PLUS;

	keyMap[AKEYCODE_DPAD_UP] = KEY_UP;
	keyMap[AKEYCODE_DPAD_DOWN] = KEY_DOWN;
	keyMap[AKEYCODE_DPAD_RIGHT] = KEY_RIGHT;
	keyMap[AKEYCODE_DPAD_LEFT] = KEY_LEFT;
	keyMap[AKEYCODE_INSERT] = KEY_INSERT;
	keyMap[AKEYCODE_MOVE_HOME] = KEY_HOME;
	keyMap[AKEYCODE_MOVE_END] = KEY_END;
	keyMap[AKEYCODE_PAGE_UP] = KEY_PAGEUP;
	keyMap[AKEYCODE_PAGE_DOWN] = KEY_PAGEDOWN;

	keyMap[AKEYCODE_F1] = KEY_F1;
	keyMap[AKEYCODE_F2] = KEY_F2;
	keyMap[AKEYCODE_F3] = KEY_F3;
	keyMap[AKEYCODE_F4] = KEY_F4;
	keyMap[AKEYCODE_F5] = KEY_F5;
	keyMap[AKEYCODE_F6] = KEY_F6;
	keyMap[AKEYCODE_F7] = KEY_F7;
	keyMap[AKEYCODE_F8] = KEY_F8;
	keyMap[AKEYCODE_F9] = KEY_F9;
	keyMap[AKEYCODE_F10] = KEY_F10;
	keyMap[AKEYCODE_F11] = KEY_F11;
	keyMap[AKEYCODE_F12] = KEY_F12;

	keyMap[AKEYCODE_NUM_LOCK] = KEY_NUMLOCK;
	keyMap[AKEYCODE_CAPS_LOCK] = KEY_CAPSLOCK;
	keyMap[AKEYCODE_SCROLL_LOCK] = KEY_SCROLLOCK;
	keyMap[AKEYCODE_SHIFT_RIGHT] = KEY_RSHIFT;
	keyMap[AKEYCODE_SHIFT_LEFT] = KEY_LSHIFT;
	keyMap[AKEYCODE_CTRL_RIGHT] = KEY_RCTRL;
	keyMap[AKEYCODE_CTRL_LEFT] = KEY_LCTRL;
	keyMap[AKEYCODE_ALT_RIGHT] = KEY_RALT;
	keyMap[AKEYCODE_ALT_LEFT] = KEY_LALT;
	keyMap[AKEYCODE_META_RIGHT] = KEY_RSUPER;
	keyMap[AKEYCODE_META_LEFT] = KEY_LSUPER;

	keyMap[AKEYCODE_HELP] = KEY_HELP;
 	keyMap[AKEYCODE_SYSRQ] = KEY_PRINT;
	keyMap[AKEYCODE_BREAK] = KEY_BREAK;
	keyMap[AKEYCODE_MENU] = KEY_MENU;

}

PolyKEY AndroidCore::mapKey(int keyCode){
	return keyMap[(unsigned int) keyCode];
}

