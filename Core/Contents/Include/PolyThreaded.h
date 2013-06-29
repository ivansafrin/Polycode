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

namespace Polycode{

class Core;
class CoreMutex;

/**
* An easy way to create threaded processes. If you subclass this class, you can implement the updateThread method, which will be called in its own thread repeatedly until threadRunning is false once the thread is created. If you only need to run through something once, make sure to set threadRunning to avoid it being called again. 

	To create the thread, pass your Threaded subclass to createThread method of Core.
	@see Core
*/
class _PolyExport Threaded : public EventDispatcher {
	public:
		Threaded();
		virtual ~Threaded();

		/**
		* Sets the thread running flag to false.
		*/ 
		virtual void killThread();
		virtual void runThread();

		/**
		* Implement this method with your own code.
		*/
		virtual void updateThread() {};

		void dispatchEvent(Event *event, int eventCode);
		void dispatchEventNoDelete(Event *event, int eventCode);

		bool threadRunning;

		Core *core;

		bool scheduledForRemoval;

		CoreMutex *eventMutex;
		std::vector<Event*> eventQueue;
};

}
