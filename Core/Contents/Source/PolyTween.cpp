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

#include "PolyTween.h"
#include "PolyBezierCurve.h"
#include "PolyCoreServices.h"
#include "PolyQuaternionCurve.h"
#include "PolyTimer.h"
#include "PolyTweenManager.h"
#include "PolyTimerManager.h"
#include "PolyEvent.h"

using namespace Polycode;

Tween::Tween(Number *target, int easeType, Number startVal, Number endVal, Number time, bool repeat, bool deleteOnComplete, Number waitTime) : EventDispatcher() {
	this->waitTime = waitTime;
	this->deleteOnComplete = deleteOnComplete;
	targetVal = target;
	this->repeat = repeat;
	this->easeType = easeType;
	this->endVal = endVal;
	this->startVal = startVal;
	cVal = endVal - startVal;
	localTargetVal = startVal;
	this->endTime = time;
	tweenTime = 0;
	if(waitTime == 0.0)
		*targetVal = startVal;
	tweenTimer = new Timer(true, 1);
	tweenTimer->addEventListener(this, 0);
	complete = false;

	actEndTime = time;
	CoreServices::getInstance()->getTweenManager()->addTween(this);
}

void Tween::Pause(bool pauseVal) {
	tweenTimer->Pause(pauseVal);
}

void Tween::setSpeed(Number speed) {
	if(speed <= 0 )
		endTime = 0;
	else
		endTime = actEndTime / speed;
}

Tween::~Tween() {
	tweenTimer->removeEventListener(this, 0);
	delete tweenTimer;

	deleteOnComplete = false; // Prevent loop when we removeTween in next line.
	CoreServices::getInstance()->getTweenManager()->removeTween(this);
}

bool Tween::isComplete() {
	return complete;
}

void Tween::doOnComplete() {
	dispatchEvent(new Event(), Event::COMPLETE_EVENT);
}

void Tween::handleEvent(Event *event) {
	if(tweenTime >= endTime+waitTime) {
		if(repeat){
			Reset();
			updateCustomTween();
		} else {
			*targetVal = endVal;
			complete = true;
		}
		return;
	}

	if(targetVal != NULL && tweenTime > waitTime) {
		localTargetVal = interpolateTween();
		*targetVal = localTargetVal;
	}
	tweenTime += tweenTimer->getElapsedf();
	updateCustomTween();
}

void Tween::Reset() {
	tweenTime = 0;
	complete = false;
}

Number Tween::interpolateTween() {
	Number t = tweenTime-waitTime;

	switch(easeType) {
		case EASE_IN_QUAD:
			t /= endTime;
			return cVal*t*t + startVal;
		break;
		case EASE_OUT_QUAD:
			t /= endTime;
			return -cVal * t*(t-2.0f) + startVal;
		break;
		case EASE_INOUT_QUAD:
			t /= endTime/2.0f;
			if (t < 1.0f) 
				return cVal/2.0f*t*t + startVal;
			t--;
			return -cVal/2.0f * (t*(t-2.0f) - 1.0f) + startVal;
		break;
		case EASE_IN_CUBIC:
			t /= endTime;
			return cVal*t*t*t + startVal;
		break;
		case EASE_OUT_CUBIC:
			t /= endTime;
			t--;
			return cVal*(t*t*t + 1.0f) + startVal;
		break;
		case EASE_INOUT_CUBIC:
			t /= endTime/2.0f;
			if (t < 1.0f) 
				return cVal/2.0f*t*t*t + startVal;
			t -= 2.0f;
			return cVal/2.0f*(t*t*t + 2.0f) + startVal;
		break;
		case EASE_IN_QUART:
			t /= endTime;
			return cVal*t*t*t*t + startVal;
		break;
		case EASE_OUT_QUART:
			t /= endTime;
			t--;
			return -cVal * (t*t*t*t - 1.0f) + startVal;
		break;
		case EASE_INOUT_QUART:
			t /= endTime/2.0f;
			if (t < 1.0f) 
				return cVal/2.0f*t*t*t*t + startVal;
			t -= 2.0f;
			return -cVal/2.0f * (t*t*t*t - 2.0f) + startVal;
		break;
		case EASE_IN_QUINT:
			t /= endTime;
			return cVal*t*t*t*t*t + startVal;
		break;
		case EASE_OUT_QUINT:
			t /= endTime;
			t--;
			return cVal*(t*t*t*t*t + 1.0f) + startVal;
		break;
		case EASE_INOUT_QUINT:
			t /= endTime/2.0f;
			if (t < 1.0f) 
				return cVal/2.0f*t*t*t*t*t + startVal;
			t -= 2.0f;
			return cVal/2.0f*(t*t*t*t*t + 2.0f) + startVal;
		break;
		case EASE_IN_SINE:
			return -cVal * cos(t/endTime * (PI/2.0f)) + cVal + startVal;
		break;
		case EASE_OUT_SINE:
			return cVal * sin(t/endTime * (PI/2.0f)) + startVal;
		break;
		case EASE_INOUT_SINE:
			return -cVal/2.0f * (cos(PI*t/endTime) - 1.0f) + startVal;
		break;
		case EASE_IN_EXPO:
			return cVal * powf( 2.0f, 10.0f * (t/endTime - 1.0f) ) + startVal;
		break;
		case EASE_OUT_EXPO:
			return cVal * ( -powf( 2.0f, -10.0f * t/endTime ) + 1.0f ) + startVal;
		break;
		case EASE_INOUT_EXPO:
			t /= endTime/2.0f;
			if (t < 1.0f) 
				return cVal/2.0f * powf( 2.0f, 10.0f * (t - 1.0f) ) + startVal;
			t--;
			return cVal/2.0f * ( -powf( 2.0f, -10.0f * t) + 2.0f ) + startVal;
		break;
		case EASE_IN_CIRC:
			t /= endTime;
			return -cVal * (sqrt(1.0f - t*t) - 1.0f) + startVal;
			break;	
		case EASE_OUT_CIRC:
			t /= endTime;
			t--;
			return cVal * sqrt(1.0f - t*t) + startVal;
		break;
		case EASE_INOUT_CIRC:
			t /= endTime/2.0f;
			if (t < 1.0f)
				return -cVal/2.0f * (sqrt(1.0f - t*t) - 1.0f) + startVal;
			t -= 2.0f;
			return cVal/2.0f * (sqrt(1.0f - t*t) + 1.0f) + startVal;
		break;
		case EASE_OUT_BOUNCE:
		case EASE_INOUT_BOUNCE:
		case EASE_IN_BOUNCE:
			if ((t/=endTime) < (1/2.75)) {
				return cVal*(7.5625*t*t) + startVal;
			} else if (t < (2/2.75)) {
				return cVal*(7.5625*(t-=(1.5/2.75))*t + .75) + startVal;
			} else if (t < (2.5/2.75)) {
				return cVal*(7.5625*(t-=(2.25/2.75))*t + .9375) + startVal;
			} else {
				return cVal*(7.5625*(t-=(2.625/2.75))*t + .984375) + startVal;
			}
		break;
		default:
		case EASE_NONE:
			// return c*t/d + b;
			return cVal*t/endTime+startVal;
		break;
	}
}

BezierPathTween::BezierPathTween(Vector3 *target, BezierCurve *curve, int easeType, Number time, bool repeat) : Tween(&pathValue, easeType, 0.0f, 1.0f, time, repeat) {
	this->curve = curve;
	this->target = target;
	pathValue = 0;
}

void BezierPathTween::updateCustomTween() {
	*target = curve->getPointAt(pathValue);
}

BezierPathTween::~BezierPathTween() {

}

QuaternionTween::QuaternionTween(Quaternion *target, BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve, int easeType, Number time, bool repeat) : Tween(&pathValue, easeType, 0.0f, 1.0f, time, repeat) {
	this->quatCurve = new QuaternionCurve(wCurve, xCurve, yCurve, zCurve);
	this->target = target;
	pathValue = 0;

}

QuaternionTween::~QuaternionTween() {
}

void QuaternionTween::updateCustomTween() {
	*target = quatCurve->interpolate(pathValue, true);
}

