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

//#ifdef _WINDOWS
	overrideInstance = new CoreServices;
	overrideInstance->drawScreensFirst = false;
	Logger::log("Creating new core services instance...\n");
	return overrideInstance;
//#else
//	long threadID = getThreadID(); 
//	CoreServices *instance;
//	if(instanceMap.find(threadID) == instanceMap.end()) {
//		Logger::log("Creating new core services instance...\n");
//		instance = new CoreServices;
//		instanceMap[threadID] = instance;
//	} else {
//		instance = instanceMap[threadID];
//	}
//	return instance;
//#endif
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

Logger *CoreServices::getLogger() {
	return logger;
}

void CoreServices::installModule(PolycodeModule *module)  {
	modules.push_back(module);
	if(module->requiresUpdate()) {
		updateModules.push_back(module);
	}

	switch(module->getType()) {
		case PolycodeModule::TYPE_SHADER:
//			renderer->addShaderModule((ShaderModule*)module);
			resourceManager->addShaderModule((PolycodeShaderModule*) module);
			materialManager->addShaderModule((PolycodeShaderModule*) module);
			renderer->addShaderModule((PolycodeShaderModule*) module);
		break;
	}
}

void CoreServices::setupBasicListeners() {
	this->setCore(this->core);
}

CoreServices::CoreServices() : EventDispatcher() {
	logger = new Logger();
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
	addEventListener(screenManager, InputEvent::EVENT_TOUCHES_BEGAN);
	addEventListener(screenManager, InputEvent::EVENT_TOUCHES_ENDED);
	addEventListener(screenManager, InputEvent::EVENT_TOUCHES_MOVED);
	sceneManager = new SceneManager();
	timerManager = new TimerManager();
	tweenManager = new TweenManager();
	soundManager = new SoundManager();
	fontManager = new FontManager();

	focusedChild = NULL;
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
	core->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_BEGAN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_ENDED);
	core->getInput()->addEventListener(this, InputEvent::EVENT_TOUCHES_MOVED);
}

void CoreServices::handleEvent(Event *event) {
	if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
			case InputEvent::EVENT_KEYUP:
				dispatchEvent(new InputEvent(inputEvent->key, inputEvent->charCode, inputEvent->timestamp), inputEvent->getEventCode());
			break;
			case InputEvent::EVENT_TOUCHES_BEGAN:
			case InputEvent::EVENT_TOUCHES_ENDED:
			case InputEvent::EVENT_TOUCHES_MOVED:
			{
				InputEvent *event = new InputEvent();
				event->touches = inputEvent->touches;
				event->timestamp = inputEvent->timestamp;
				dispatchEvent(event, inputEvent->getEventCode());
			}
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

void CoreServices::Render() {
	if(renderer->doClearBuffer)
		renderer->clearScreen();

	renderer->setPerspectiveMode();
	sceneManager->renderVirtual();
	if(renderer->doClearBuffer)
		renderer->clearScreen();

	if(drawScreensFirst) {
		renderer->clearLights();
		screenManager->Render();
		renderer->setPerspectiveMode();
		sceneManager->Render();
	} else {
		sceneManager->Render();
		renderer->clearLights();
		screenManager->Render();
	}
}

void CoreServices::Update(int elapsed) {
	
	for(int i=0; i < updateModules.size(); i++) {
		updateModules[i]->Update(elapsed);
	}
	resourceManager->Update(elapsed);
	timerManager->Update();
	tweenManager->Update();
	materialManager->Update(elapsed);
	sceneManager->Update();
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

