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

#include "PolyTweenManager.h"
#include "PolyTween.h"

using namespace Polycode;

TweenManager::TweenManager() {

}

TweenManager::~TweenManager() {

}

void TweenManager::addTween(Tween *tween) {
	tweens.push_back(tween);
}

void TweenManager::removeTween(Tween *tween) {
	for(int i=0;i<tweens.size();i++) {
		if(tweens[i] == tween) {
			tweens.erase(tweens.begin()+i);
			if(tween->deleteOnComplete)
				delete tween;

		}
	}
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
				if(tween->deleteOnComplete)
					delete tween;
				return;
			}
		}
	}
}
