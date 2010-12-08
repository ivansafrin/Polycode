/*
 *  ScreenManager.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyScreenManager.h"

using namespace Polycode;

ScreenManager::ScreenManager() : EventDispatcher() {

}

ScreenManager::~ScreenManager() {

}

void ScreenManager::removeScreen(Screen *screen) {
	for(int i=0;i<screens.size();i++) {
		if(screens[i] == screen) {
			screens.erase(screens.begin()+i);
			delete screen;
		}
	}
}

void ScreenManager::addScreen(Screen *screen) {
	screen->setRenderer(CoreServices::getInstance()->getRenderer());
	screens.push_back(screen);
}

void ScreenManager::handleEvent(Event *event) {
//	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;
		for(int i=0;i<screens.size();i++) {
			screens[i]->handleInputEvent(inputEvent);
		}
//	}
}

/*
Screen *ScreenManager::createScreen(int screenType) {

	Screen *screen;
	switch(screenType) {
		case REGULAR_SCREEN:
			screen = new Screen();
		break;
		case PHYSICS_SCREEN:
			screen = new PhysicsScreen();
		break;
	}
	
	screen->setRenderer(CoreServices::getInstance()->getRenderer());
	screens.push_back(screen);
	return screen;
}
*/

void ScreenManager::Update() {
	for(int i=0;i<screens.size();i++) {
		if(screens[i]->enabled)
			if(screens[i]->hasFilterShader()) {
				screens[i]->drawFilter();
			} else {
				screens[i]->Render();
			}
	}
}