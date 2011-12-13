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

#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyCoreInput.h"
#include "PolyInputEvent.h"
#include "PolyLogger.h"
#include "PolyModule.h"
#include "PolyResourceManager.h"
#include "PolyMaterialManager.h"
#include "PolyRenderer.h"
#include "PolyConfig.h"
#include "PolyFontManager.h"
#include "PolyScreenManager.h"
#include "PolySceneManager.h"
#include "PolyTimerManager.h"
#include "PolyTweenManager.h"
#include "PolySoundManager.h"

// For use by getScreenInfo
#if defined(_WINDOWS)
#include <windows.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <ApplicationServices/ApplicationServices.h>
#elif defined(__linux) || defined(__linux__) || defined(linux)
#include <X11/extensions/Xrandr.h>
#include <gdk/gdkx.h>
#elif defined(SDL_VERSION)
#include <SDL/SDL.h>
#endif

using namespace Polycode;

std::map<long, CoreServices*> CoreServices::instanceMap;
CoreMutex *CoreServices::renderMutex = 0;
CoreServices* CoreServices::overrideInstance = NULL;

CoreMutex *CoreServices::getRenderMutex() {
	if(renderMutex == NULL) {
		Logger::log("Creating render mutex...\n");
		renderMutex = getInstance()->getCore()->createMutex();
	}
	return renderMutex;
}

void CoreServices::setInstance(CoreServices *_instance) {
	overrideInstance = _instance;
	Logger::log("Overriding core instance...\n");
}

CoreServices* CoreServices::getInstance() {

	if(overrideInstance) {
		return overrideInstance;
	}

#ifdef _WINDOWS
		overrideInstance = new CoreServices;
		Logger::log("Creating new core services instance...\n");
		return overrideInstance;
#else
	long threadID = getThreadID(); 
	CoreServices *instance;
	if(instanceMap.find(threadID) == instanceMap.end()) {
		Logger::log("Creating new core services instance...\n");
		instance = new CoreServices;
		instanceMap[threadID] = instance;
	} else {
		instance = instanceMap[threadID];
	}
	return instance;
#endif
}

MaterialManager *CoreServices::getMaterialManager() {
	return materialManager;
}

TimerManager *CoreServices::getTimerManager() {
	return timerManager;
}

FontManager *CoreServices::getFontManager() {
	return fontManager;
}

Config *CoreServices::getConfig() {
	return config;
}

void CoreServices::installModule(PolycodeModule *module)  {
	modules.push_back(module);
	switch(module->getType()) {
		case PolycodeModule::TYPE_SHADER:
//			renderer->addShaderModule((ShaderModule*)module);
			resourceManager->addShaderModule((PolycodeShaderModule*) module);
			materialManager->addShaderModule((PolycodeShaderModule*) module);
			renderer->addShaderModule((PolycodeShaderModule*) module);
		break;
	}
}

CoreServices::CoreServices() : EventDispatcher() {
	resourceManager = new ResourceManager();	
	config = new Config();
	materialManager = new MaterialManager();
	screenManager = new ScreenManager();
	addEventListener(screenManager, InputEvent::EVENT_MOUSEDOWN);
	addEventListener(screenManager, InputEvent::EVENT_MOUSEMOVE);
	addEventListener(screenManager, InputEvent::EVENT_MOUSEUP);
	addEventListener(screenManager, InputEvent::EVENT_MOUSEWHEEL_UP);
	addEventListener(screenManager, InputEvent::EVENT_MOUSEWHEEL_DOWN);	
	addEventListener(screenManager, InputEvent::EVENT_KEYDOWN);
	addEventListener(screenManager, InputEvent::EVENT_KEYUP);	
	sceneManager = new SceneManager();
	timerManager = new TimerManager();
	tweenManager = new TweenManager();
	soundManager = new SoundManager();
	fontManager = new FontManager();
}

CoreServices::~CoreServices() {
	delete materialManager;
	delete screenManager;
	delete sceneManager;
	delete timerManager;
	delete tweenManager;
	delete resourceManager;
	delete soundManager;
	delete fontManager;
	instanceMap.clear();
	overrideInstance = NULL;
	
}

void CoreServices::setCore(Core *core) {
	this->core = core;
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);	
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);		
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
}

void CoreServices::handleEvent(Event *event) {
	if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
			case InputEvent::EVENT_KEYUP:
				dispatchEvent(new InputEvent(inputEvent->key, inputEvent->charCode, inputEvent->timestamp), inputEvent->getEventCode());			
			break;
			default:
				InputEvent *_inputEvent = new InputEvent(inputEvent->mousePosition, inputEvent->timestamp);
				_inputEvent->mouseButton = inputEvent->mouseButton;
				dispatchEvent(_inputEvent, inputEvent->getEventCode());			
			break;
		}
	}
}

Core *CoreServices::getCore() {
	return core;
}


void CoreServices::setRenderer(Renderer *renderer) {
	this->renderer = renderer;
}

Renderer *CoreServices::getRenderer() {
	return renderer;
}

void CoreServices::Update(int elapsed) {
	timerManager->Update();
	tweenManager->Update();
	materialManager->Update(elapsed);
	renderer->setPerspectiveMode();
	sceneManager->UpdateVirtual();
	renderer->clearScreen();
	sceneManager->Update();
//	renderer->setOrthoMode();
	screenManager->Update();
}

SoundManager *CoreServices::getSoundManager() {
	return soundManager;
}

ScreenManager *CoreServices::getScreenManager() {
	return screenManager;
}

SceneManager *CoreServices::getSceneManager() {
	return sceneManager;
}

TweenManager *CoreServices::getTweenManager() {
	return tweenManager;
}

ResourceManager *CoreServices::getResourceManager() {
	return resourceManager;
}

void CoreServices::getScreenInfo(int *width, int *height, int *hz) {
#if defined(_WINDOWS)
	
	DEVMODE mode = {.dmSize = sizeof(DEVMODE), .dmDriverExtra = 0};
	
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &mode);
	
    // Store the current display settings.
    if (width) *width = mode.dmPelsWidth;
    if (height) *height = mode.dmPelsHeight;
    if (hz) *hz = mode.dmDisplayFrequency;
	
#elif defined(__APPLE__) && defined(__MACH__)
	
	CGDisplayModeRef mode = CGDisplayCopyDisplayMode(CGMainDisplayID());
    
    // Copy the relevant data.
    if (width) *width = CGDisplayModeGetWidth(mode);
    if (height) *height = CGDisplayModeGetHeight(mode);
    if (hz) *hz = CGDisplayModeGetRefreshRate(mode);
    
    CGDisplayModeRelease(mode);
	
#elif defined(__linux) || defined(__linux__) || defined(linux)
	
    // Get the current configuration.
    XRRScreenConfiguration *config = XRRGetScreenInfo(gdk_x11_get_default_xdisplay(),
                                                      gdk_x11_get_default_root_xwindow());
    int size_count;
    // Obtain the dimensions.
    XRRScreenSize *sizes = XRRConfigSizes(config, &size_count);
    Rotation current_rotation;
    SizeID current_mode = XRRConfigCurrentConfiguration(config, &current_rotation);
	
    // Store the results.
    if (width) *width = sizes[current_mode].width;
    if (height) *height = sizes[current_mode].height;
    if (hz) *hz = XRRConfigCurrentRate(config); // Warning: On some drivers (nvidia?) this can lie.
	
    XRRFreeScreenConfigInfo(config);
	
#elif defined(SDL_VERSION)
	
	const SDL_VideoInfo *video = SDL_GetVideoInfo();
	if (width) *width = video->current_w;
	if (height) *height = video->current_h;
	if (hz) *hz = 0;
	
#else
	
	if (width) *width = 0;
	if (height) *height = 0;
	if (hz) *hz = 0;
	
#endif
}