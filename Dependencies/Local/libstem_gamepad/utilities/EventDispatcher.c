/*
  Copyright (c) 2010 Alex Diener
  
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.
  
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  
  Alex Diener adiener@sacredsoftware.net
*/

#include "utilities/EventDispatcher.h"

#include <stdlib.h>
#include <string.h>

struct EventTarget {
	char * eventID;
	EventDispatcherCallback callback;
	void * context;
};

EventDispatcher * EventDispatcher_create(void * owner) {
	EventDispatcher * self;
	
	self = malloc(sizeof(EventDispatcher));
	EventDispatcher_init(self, owner);
	return self;
}

void EventDispatcher_init(EventDispatcher * self, void * owner) {
	self->dispose = EventDispatcher_dispose;
	self->registerForEvent = EventDispatcher_registerForEvent;
	self->unregisterForEvent = EventDispatcher_unregisterForEvent;
	self->dispatchEvent = EventDispatcher_dispatchEvent;
	
	self->owner = owner;
	self->numberOfTargets = 0;
	self->targetListSize = 1;
	self->targets = (struct EventTarget *) malloc(sizeof(struct EventTarget) * self->targetListSize);
}

void EventDispatcher_dispose(void * selfPtr) {
	EventDispatcher * self = selfPtr;
	int targetIndex;
	
	for (targetIndex = 0; targetIndex < self->numberOfTargets; targetIndex++) {
		free(self->targets[targetIndex].eventID);
	}
	free(self->targets);
}

void EventDispatcher_registerForEvent(void * selfPtr, const char * eventID, EventDispatcherCallback callback, void * context) {
	EventDispatcher * self = selfPtr;
	size_t length;
	
	if (self->numberOfTargets >= self->targetListSize) {
		self->targetListSize *= 2;
		self->targets = (struct EventTarget *) realloc(self->targets, sizeof(struct EventTarget) * self->targetListSize);
	}
	
	length = strlen(eventID);
	self->targets[self->numberOfTargets].eventID = malloc(length + 1);
	strncpy(self->targets[self->numberOfTargets].eventID, eventID, length + 1);
	self->targets[self->numberOfTargets].callback = callback;
	self->targets[self->numberOfTargets].context = context;
	self->numberOfTargets++;
}

void EventDispatcher_unregisterForEvent(void * selfPtr, const char * eventID, EventDispatcherCallback callback) {
	EventDispatcher * self = selfPtr;
	int targetIndex;
	
	for (targetIndex = 0; targetIndex < self->numberOfTargets; targetIndex++) {
		if (!strcmp(eventID, self->targets[targetIndex].eventID) && self->targets[targetIndex].callback == callback) {
			free(self->targets[targetIndex].eventID);
			self->numberOfTargets--;
			for (; targetIndex < self->numberOfTargets; targetIndex++) {
				self->targets[targetIndex] = self->targets[targetIndex + 1];
			}
			break;
		}
	}
}

bool EventDispatcher_dispatchEvent(void * selfPtr, const char * eventID, void * eventData) {
	EventDispatcher * self = selfPtr;
	int targetIndex;
	int numberOfTargetsCopy;
	struct EventTarget * targetsCopy;
	bool eventHandled, anyEventsHandled;
	
	numberOfTargetsCopy = self->numberOfTargets;
	targetsCopy = malloc(sizeof(struct EventTarget) * numberOfTargetsCopy);
	memcpy(targetsCopy, self->targets, sizeof(struct EventTarget) * numberOfTargetsCopy);
	
	anyEventsHandled = false;
	for (targetIndex = 0; targetIndex < numberOfTargetsCopy; targetIndex++) {
		if (!strcmp(eventID, self->targets[targetIndex].eventID)) {
			eventHandled = targetsCopy[targetIndex].callback(self->owner, eventID, eventData, targetsCopy[targetIndex].context);
			
			if (eventHandled) {
				anyEventsHandled = true;
			}
		}
	}
	
	free(targetsCopy);
	
	return anyEventsHandled;
}
