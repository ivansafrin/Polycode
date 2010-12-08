/*
 *  PolyTimer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyTimer.h"

using namespace Polycode;

Timer::Timer(bool triggerMode, int msecs) : EventDispatcher() {
	this->msecs = msecs;
	this->triggerMode = triggerMode;
	paused = false;
	Reset();
	CoreServices::getInstance()->getTimerManager()->addTimer(this);
}

Timer::~Timer() {
	CoreServices::getInstance()->getTimerManager()->removeTimer(this);
}

void Timer::Reset() {
	ticks = 0;
	last = 0;
	elapsed = 0;	
}

unsigned int Timer::getTicks() {
	return ticks;
}

void Timer::Pause(bool paused) {
	last = ticks;
	elapsed = 0;
	this->paused = paused;
}

float Timer::getElapsedf() {
	return ((float)(elapsed))/1000.0f;
}

bool Timer::isPaused() {
	return paused;
}

bool Timer::hasElapsed() {
	if(ticks-last > msecs) {
		last = ticks;
		return true;
	}
	return false;
}

void Timer::Update(unsigned int ticks) {
	if(last == 0) {
		last = ticks;
		return;
	}
	
	this->ticks = ticks;
	elapsed = ticks-last;
	
//	if(elapsed > 10000)
//		elapsed = 10000;
	
	if(paused)
		return;

	if(triggerMode) {
		if(elapsed > msecs) {
			last = ticks;
			this->dispatchEvent(new Event(), EVENT_TRIGGER); 
		} else {
		}
	}
}