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
#include "PolyString.h"

namespace Polycode {

	class EventDispatcher;
	
	/**
	* Event base class. Subclass this class to pass complex data through events.
	*/
	class _PolyExport Event : public PolyBase {
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
			virtual ~Event();
			
			/**
			* Returns the event code for this event.
			* @return Event code for the event.
			*/ 						
			int getEventCode() const;
			
			/**
			* Returns the event dispatcher which originated the event.
			* @return Event dispatcher which originated the event.
			*/ 									
			EventDispatcher *getDispatcher() const;
			
			void setEventCode(int eventCode);			
			void setDispatcher(EventDispatcher *dispatcher);
			const String& getEventType() const;
			
			// In order to prevent "namespace" collisions between events of different types, all event integers must be unique.
			// This is managed by arbitrarily assigning each class a "base" constant, and adding it to all its event type constants.
			// Bases for all Polycode classes are documented below, third party event types should be EVENTBASE_NONPOLYCODE or over.
			// Note that collisions are usually safe as long as collisions do not occur between a class and its subclass.
			// Event		0x100
			// Core			0x200
			// PlatformCore 0x300 (e.g. CocoaCore, WinCore etc)
			// InputEvent	0x400
			// SocketEvent	0x500
			// ClientEvent	0x600
			// ServerEvent	0x700
			// PhysicsScreenEvent	0x800
			// PhysicsSceneEvent	0x900
			// UIEvent		0xA00
			// UITreeEvent	0xB00
		
			static const int EVENTBASE_EVENT = 0x100;
			static const int COMPLETE_EVENT = EVENTBASE_EVENT+0;
			static const int CHANGE_EVENT = EVENTBASE_EVENT+1;
			static const int CANCEL_EVENT = EVENTBASE_EVENT+2;
			static const int NOTIFY_EVENT = EVENTBASE_EVENT+3;
			static const int FIRE_EVENT = EVENTBASE_EVENT+4;
			static const int RESOURCE_RELOAD_EVENT = EVENTBASE_EVENT+5;
			static const int SELECT_EVENT = EVENTBASE_EVENT+6;
			static const int REMOVE_EVENT = EVENTBASE_EVENT+7;
			static const int RESOURCE_CHANGE_EVENT = EVENTBASE_EVENT+8;
																		
			static const int EVENTBASE_NONPOLYCODE = 0x10000;
		
			bool deleteOnDispatch;
						
		protected:
			
			String eventType;
			EventDispatcher *dispatcher;
			int eventCode;
			
	};
}
