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

#include "PolyTimer.h"
#include "PolyCoreServices.h"
#include "PolyTimerManager.h"
#include "PolyEvent.h"

using namespace Polycode;

Timer::Timer(bool triggerMode, int msecs) : EventDispatcher() {
	this->msecs = msecs;
	this->triggerMode = triggerMode;
	paused = false;
	Reset();
	CoreServices::getInstance()->getTimerManager()->addTimer(this);
}

void Timer::setTimerInterval(int msecs) {
	this->msecs = msecs;
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

Number Timer::getElapsedf() {
	return ((Number)(elapsed))/1000.0f;
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

	if(paused)
		return;

	if(triggerMode && elapsed > msecs) {
		last = ticks;
		this->dispatchEvent(new Event(), EVENT_TRIGGER); 
	}
}
