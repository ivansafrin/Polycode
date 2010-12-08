/*
 *  PolyTweenManager.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyTweenManager.h"

using namespace Polycode;

TweenManager::TweenManager() {

}

TweenManager::~TweenManager() {

}

void TweenManager::addTween(Tween *tween) {
	tweens.push_back(tween);
}

void TweenManager::Update() {
	Tween *tween;
	for(int i=0;i<tweens.size();i++) {
		if(tweens[i]->isComplete()) {
			if(tweens[i]->repeat) {
				tweens[i]->Reset();
				return;
			} else {
				tween = tweens[i];
				tweens.erase(tweens.begin()+i);
				tween->doOnComplete();
				delete tween;
				return;
			}
		}
	}
}
