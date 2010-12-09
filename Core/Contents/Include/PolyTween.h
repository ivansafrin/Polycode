/*
 *  PolyTween.h
 *  Poly
 *
 *  Created by Ivan Safrin on 7/7/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyEventDispatcher.h"
#include "PolyCoreServices.h"
#include "PolyBezierCurve.h"
#include "PolyQuaternionCurve.h"

namespace Polycode {
	
	class Timer;
	
	class _PolyExport Tween : public EventDispatcher {
	public:
		Tween(float *target, int easeType, float startVal, float endVal, float time, bool repeat=false);
		~Tween();
		
		void handleEvent(Event *event);
		float interpolateTween();
		virtual void updateCustomTween() {}
		void doOnComplete();
		
		void Pause(bool pauseVal);
		
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
		
		void setSpeed(float speed);
		

	protected:
	
		
		int easeType;
		bool complete;
		float endVal;
		float cVal;
		float startVal;
		float actEndTime;
		float endTime;
		float *targetVal;
		float localTargetVal;
		float tweenTime;
		Timer *tweenTimer;
	};
	
	class _PolyExport BezierPathTween : public Tween {
		public:
			BezierPathTween(Vector3 *target, BezierCurve *curve, int easeType, float time, bool repeat=false);
			~BezierPathTween();
			void updateCustomTween();

		protected:
			float pathValue;
			Tween *pathTween;
			BezierCurve *curve;
			Vector3 *target;
	};
	
	class _PolyExport QuaternionTween : public Tween {
		public:
			QuaternionTween(Quaternion *target, BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve,
							BezierCurve *zCurve, int easeType, float time, bool repeat=false);
			~QuaternionTween();
			void updateCustomTween();
		private:
			float pathValue;
			Tween *pathTween;
			QuaternionCurve	*quatCurve;
			Quaternion *target;			
	};
	
}
