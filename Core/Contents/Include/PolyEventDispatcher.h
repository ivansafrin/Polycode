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
#include "PolyGlobals.h"
#include "PolyEventHandler.h"
#include <vector>

namespace Polycode {

	class Event;

typedef struct {
	EventHandler *handler;
	int eventCode;
} EventEntry;

	/**
	* Can dispatch events. The event dispatcher is base class which allows its subclass to dispatch custom events which EventHandler subclasses can then listen to. EventDispatcher and EventHandler are the two main classes in the Polycode event system. If you are familiar with ActionScript3's event system, you will find this to be very similar, except that it uses integers for event codes for speed, rather than strings.
	*/	
	class _PolyExport EventDispatcher : public EventHandler {
		public:
			/**
			* Default constructor
			*/
			EventDispatcher();
			virtual ~EventDispatcher();
			
			/**
			* Removes all current event handlers from this dispatcher.
			*/
			void removeAllHandlers();
			
			/**
			* Removes all current event handlers from this dispatcher for a specific event listener.
			* @param Event listener to remove handlers for.
			*/			
			void removeAllHandlersForListener(EventHandler *handler);
			
			/**
			* Adds an event listener for a specific event code. Once a listener is registered for a specific event code, that listener will start getting event callbacks into the handleEvent() method.
			* @param handler The event handler to add as a listener
			* @param eventCode The requested event code to listen to.
			* @see EventHandler
			*/						
			void addEventListener(EventHandler *handler, int eventCode);
        
            /**
             * Adds an event listener for specified event code if it hasn't already been added, otherwise does nothing.
             * @param handler The event handler to add as a listener
             * @param eventCode The requested event code to listen to.
             */
			void addEventListenerUnique(EventHandler *handler, int eventCode);
        
            /**
             * Returns true if this event dispatcher is registered with the specified EventHandler with the specified event code.
             * @param handler EventHandler to check.
             * @param eventCode The event code to check.
             */
            bool hasEventListener(EventHandler *handler, int eventCode);
        
			/**
			* Removes a listener for a specific handler and event code. 
			* @param handler The event handler to remove as a listener
			* @param eventCode The requested event code to remove listener for.
			* @see EventHandler
			*/									
			void removeEventListener(EventHandler *handler, int eventCode);
			
			void __dispatchEvent(Event *event, int eventCode);	
			
			/**
			* Dispatches an event to all handlers listening for the event code specified.
			* @param event Event class to dispatch to listeners. You can subclass the Event class to send data in your events.			
			* @param eventCode The event code to dispatch the event for.
			* @see Event
			* @see EventHandler			
			*/														
			virtual void dispatchEvent(Event *event, int eventCode);
			virtual void dispatchEventNoDelete(Event *event, int eventCode);
		
		protected:
	
		std::vector<EventEntry> handlerEntries;
	
	};
}
