/*
 *  PolyCore.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/12/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyCore.h"

namespace Polycode {
	
	Core::Core(int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate) : EventDispatcher() {
		services = CoreServices::getInstance();
		input = new CoreInput();
		services->setCore(this);
		fps = 0;
		running = true;
		frames = 0;
		lastFrameTicks=0;
		lastFPSTicks=0;
		elapsed = 0;
		this->xRes = xRes;
		this->yRes = yRes;
		mouseEnabled = true;
		lastSleepFrameTicks = 0;
		
		refreshInterval = 1000 / frameRate;
	}
	
	void Core::enableMouse(bool newval) {
		mouseEnabled = newval;
	}
	
	int Core::getNumVideoModes() {
		return numVideoModes;
	}
	
	Number Core::getXRes() {
		return xRes;
	}

	Number Core::getYRes() {
		return yRes;
	}
	
	CoreInput *Core::getInput() {
		return input;
	}	
	
	Core::~Core() {
		printf("Shutting down core");
		delete services;
	}
	
	void Core::Shutdown() {	
		running = false;
	}
	
	Number Core::getElapsed() {
		return ((Number)elapsed)/1000.0f;
	}
	
	Number Core::getTicksFloat() {
		return ((Number)getTicks())/1000.0f;		
	}
	
	void Core::setVideoModeIndex(int index, bool fullScreen, int aaLevel) {
		vector<Rectangle> resList = getVideoModes();
		if(index >= resList.size())
			return;
		
		setVideoMode(resList[index].w, resList[index].h, fullScreen, aaLevel);
	}
	
	void Core::updateCore() {
		frames++;
		frameTicks = getTicks();
		elapsed = frameTicks - lastFrameTicks;
		
		if(elapsed > refreshInterval)
			elapsed = refreshInterval;
		services->Update(elapsed);

		if(frameTicks-lastFPSTicks >= 1000) {
			fps = frames;
			frames = 0;
			lastFPSTicks = frameTicks;
		}
		lastFrameTicks = frameTicks;
		
	}
	
	void Core::doSleep() {
		unsigned int ticks = getTicks();
		unsigned int ticksSinceLastFrame = ticks - lastSleepFrameTicks;
		if(ticksSinceLastFrame <= refreshInterval)
			usleep((refreshInterval - ticksSinceLastFrame) * 1000);
		lastSleepFrameTicks = ticks;
	}
	
	
	Number Core::getFPS() {
		return fps;
	}
	
	CoreServices *Core::getServices() {
		return services;
	}
	
}