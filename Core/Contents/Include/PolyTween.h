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

#pragma once
#include "PolyGlobals.h"
#include "PolyVector3.h"
#include "PolyEventDispatcher.h"

namespace Polycode {
	
	class BezierCurve;
	class Timer;
	class Quaternion;
	class QuaternionCurve;
	
	/**
	* Tween animation class. This class lets you tween a floating point value over a period of time with different easing types.
	*/	
	class _PolyExport Tween : public EventDispatcher {
	public:
		
		/**
		* Constructor.
		* @param target Pointer to the Number to tween
		* @param easeType Easing type. See the static members of this class for the different types of easing you can use.
		* @param startVal Starting value of the number at tween's start.
		* @param endVal The value to tween the number to.
		* @param time The duration of the tween.
		* @param repeat If true, this tween will repeat over and over.
		*/
		Tween(Number *target, int easeType, Number startVal, Number endVal, Number time, bool repeat=false, bool deleteOnComplete=false, Number waitTime = 0.0);
		virtual ~Tween();
		
		void updateTween(Number elapsed);
		Number interpolateTween();
		virtual void updateCustomTween() {}
		void doOnComplete();
		
		/**
		* Pauses and resumes the tween.
		* @param pauseVal If true, pauses the tweem, if false, resumes it.
		*/
		void Pause(bool pauseVal);

		/**
		* Resets the tween to starting position.
		*/		
		void Reset();
		
		static const int EASE_NONE = 0;
		static const int EASE_IN_QUAD = 1;
		static const int EASE_OUT_QUAD = 2;
		static const int EASE_INOUT_QUAD = 3;
		static const int EASE_IN_CUBIC= 4;
		static const int EASE_OUT_CUBIC= 5;
		static const int EASE_INOUT_CUBIC= 6;
		static const int EASE_IN_QUART= 7;
		static const int EASE_OUT_QUART= 8;
		static const int EASE_INOUT_QUART= 9;
		static const int EASE_IN_QUINT= 10;
		static const int EASE_OUT_QUINT= 11;
		static const int EASE_INOUT_QUINT= 12;
		static const int EASE_IN_SINE= 13;
		static const int EASE_OUT_SINE= 14;
		static const int EASE_INOUT_SINE= 15;
		static const int EASE_IN_EXPO= 16;
		static const int EASE_OUT_EXPO= 17;
		static const int EASE_INOUT_EXPO= 18;
		static const int EASE_IN_CIRC= 19;
		static const int EASE_OUT_CIRC= 20;
		static const int EASE_INOUT_CIRC= 21;
		static const int EASE_IN_BOUNCE= 22;
		static const int EASE_OUT_BOUNCE = 23;
		static const int EASE_INOUT_BOUNCE = 24;	
		
		bool isComplete();
		bool repeat;
		
		bool deleteOnComplete;
		/*
		* Set a speed multiplier for the tween
		* @param speed Speed multiplier.
		*/
		void setSpeed(Number speed);
		
		bool paused;

	protected:
	
		Number waitTime;
		int easeType;
		bool complete;
		Number endVal;
		Number cVal;
		Number startVal;
		Number actEndTime;
		Number endTime;
		Number *targetVal;
		Number localTargetVal;
		Number tweenTime;
	};
	
	/**
	* Tweens a position along a bezier path. This class automatically animates a 3d position over a 3d bezier curve. You can use it for 2d curves as well, of course, just ignore the z!
	*/
	class _PolyExport BezierPathTween : public Tween {
		public:
			/**
			* Constructor.
			* @param target Target vector to animate.
			* @param curve The curve to animate along.
			* @param easeType Easing type (@see Tween)
			* @param time The duration of the tween.
			* @param repeat If true, this tween will repeat over and over.
			*/
			BezierPathTween(Vector3 *target, BezierCurve *curve, int easeType, Number time, bool repeat=false);
			
			~BezierPathTween();
			void updateCustomTween();

		protected:
			Number pathValue;
			Tween *pathTween;
			BezierCurve *curve;
			Vector3 *target;
	};
	
	class _PolyExport QuaternionTween : public Tween {
		public:
			QuaternionTween(Quaternion *target, BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve,
							BezierCurve *zCurve, int easeType, Number time, bool repeat=false);
			~QuaternionTween();
			void updateCustomTween();
		protected:
			Number pathValue;
			Tween *pathTween;
			QuaternionCurve	*quatCurve;
			Quaternion *target;			
	};
	
}
