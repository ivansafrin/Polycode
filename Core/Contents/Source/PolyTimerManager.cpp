/*
 *  PolyTimerManager.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyTimerManager.h"

using namespace Polycode;

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

void TimerManager::removeTimer(Timer *timer) {
	for(int i=0;i<timers.size();i++) {
		if(timers[i] == timer) {
			timers.erase(timers.begin()+i);
		}
	}	
}

void TimerManager::addTimer(Timer *timer) {
	timers.push_back(timer);		
}

void TimerManager::Update() {
	int ticks = CoreServices::getInstance()->getCore()->getTicks();
	for(int i=0;i<timers.size();i++) {
		timers[i]->Update(ticks);
	}
}