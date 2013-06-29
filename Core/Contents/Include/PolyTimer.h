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
#include "PolyEventDispatcher.h"

namespace Polycode {

/** 
* A timer that dispatches trigger events.
*/ 
class _PolyExport Timer : public EventDispatcher {
	public:
		/**
		* Creates a new timer. 
		* @param triggerMode If true, will dispatch an event at the specified frequency, otherwise it will simply count time. You normally want this to be true.
		* @param msecs Timer frequency in milliseconds.
		*/
		Timer(bool triggerMode, int msecs);
		virtual ~Timer();

		/** 
		* Pauses and resumes the timer.
		* @param paused If true, pauses the timer, otherwise resumes it.
		*/ 
		void Pause(bool paused);

		/**
		* Returns true if the timer is paused.
		*/
		bool isPaused();

		unsigned int getTicks();
		void Update(unsigned int ticks);

		/**
		* Resets the timer.
		*/ 
		void Reset();
		bool hasElapsed();

		/**
		* Returns the time elapsed in floating point microseconds.
		*/
		Number getElapsedf();

		void setTimerInterval(int msecs);

		static const int EVENT_TRIGGER = 0;

	protected:

		int elapsed;
		bool paused;
		unsigned int msecs;
		bool triggerMode;
		unsigned int last;
		unsigned int ticks;
};

}
