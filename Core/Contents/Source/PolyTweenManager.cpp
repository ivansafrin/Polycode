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
#include "PolyCore.h"

using namespace Polycode;

TweenManager::TweenManager() {
}

TweenManager::~TweenManager() {

}

void TweenManager::addTween(Tween *tween) {
	tweensToAdd.push_back(tween);
}

void TweenManager::removeTween(Tween *tween) {
	for(int i=0; i < tweens.size(); i++) {
		if(tweens[i] == tween) {
			tweens.erase(tweens.begin()+i);
			return;
		}
	}
}

void TweenManager::removeTweensForTarget(Number *target) {
    std::vector<Tween*>::iterator iter = tweens.begin();
    while (iter != tweens.end()) {
        bool mustRemove = false;
        if(target == (*iter)->getTarget()) {
            mustRemove = true;
            if((*iter)->deleteOnComplete) {
                Tween *tween = (*iter);
                delete tween;
            }
        }
        
        if(mustRemove) {
            iter = tweens.erase(iter);
        } else {	
            ++iter;						
        }
    }
}

void TweenManager::Update(Number elapsed) {

	std::vector<Tween*>::iterator iter = tweens.begin();
	while (iter != tweens.end()) {	
		bool mustRemove = false;
		
		(*iter)->updateTween(elapsed/1000.0);
		
		if((*iter)->isComplete()) {
			if((*iter)->repeat) {
				(*iter)->Reset();
			} else {
				mustRemove = true;							
				(*iter)->doOnComplete();
				
				if((*iter)->deleteOnComplete) {
					Tween *tween = (*iter);
					delete tween;
				}
			}
		}
		
		if(mustRemove) {
			iter = tweens.erase(iter);
		} else {	
			++iter;						
		}
	}
	
	for(int i=0; i < tweensToAdd.size(); i++) {
		tweens.push_back(tweensToAdd[i]);
	}
	tweensToAdd.clear();
	
}
