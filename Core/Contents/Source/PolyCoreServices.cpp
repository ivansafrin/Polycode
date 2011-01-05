/*
 *  CoreServices.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyCoreServices.h"

using namespace Polycode;

std::map<long, CoreServices*> CoreServices::instanceMap;
CoreMutex *CoreServices::renderMutex = 0;


CoreMutex *CoreServices::getRenderMutex() {
	if(renderMutex == NULL) {
		Logger::log("Creating render mutex...\n");
		renderMutex = getInstance()->getCore()->createMutex();
	}
	return renderMutex;
}

CoreServices* CoreServices::getInstance() {
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
				dispatchEvent(new InputEvent(inputEvent->mousePosition, inputEvent->timestamp), inputEvent->getEventCode());			
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