/*
 *  PolyEventDispatcher.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */
// @package Events

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyEventHandler.h"
#include "PolyEvent.h"
#include <vector>

using std::vector;


namespace Polycode {


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
			void removeAllHandlersForListener(void *listener);
			
			/**
			* Adds an event listener for a specific event code. Once a listener is registered for a specific event code, that listener will start getting event callbacks into the handleEvent() method.
			* @param handler The event handler to add as a listener
			* @param eventCode The requested event code to listen to.
			* @see EventHandler
			*/						
			void addEventListener(EventHandler *handler, int eventCode);
			
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
			void dispatchEvent(Event *event, int eventCode);
			void dispatchEventNoDelete(Event *event, int eventCode);
		
		protected:
	
		vector<EventEntry> handlerEntries;
	
	};
}