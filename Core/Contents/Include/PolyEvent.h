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
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <string>

using std::string;

namespace Polycode {

	class EventDispatcher;
	
	/**
	* Event base class. Subclass this class to pass complex data through events.
	*/
	class _PolyExport Event {
		public:
			/**
			* Default constructor.
			*/ 
			Event();
			
			/**
			* Initializes the event with an eventCode
			* @param eventCode Event code to initalize with.
			*/ 			
			Event(int eventCode);
			~Event();
			
			/**
			* Returns the event code for this event.
			* @return Event code for the event.
			*/ 						
			int getEventCode();
			
			/**
			* Returns the event dispatcher which originated the event.
			* @return Event dispatcher which originated the event.
			*/ 									
			EventDispatcher *getDispatcher();
			
			void setEventCode(int eventCode);			
			void setDispatcher(EventDispatcher *dispatcher);
			String getEventType();
			
			static const int COMPLETE_EVENT = 0;
			static const int CHANGE_EVENT = 1;
						
		protected:
			
			String eventType;
			EventDispatcher *dispatcher;
			int eventCode;
			
	};
}