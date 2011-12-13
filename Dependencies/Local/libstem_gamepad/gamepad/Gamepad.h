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

#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#include <stdbool.h>
#include "utilities/EventDispatcher.h"

// eventData -> struct Gamepad_device
#define GAMEPAD_EVENT_DEVICE_ATTACHED "GAMEPAD_EVENT_DEVICE_ATTACHED" // Only dispatched when Gamepad_init or Gamepad_detectDevices is called
#define GAMEPAD_EVENT_DEVICE_REMOVED  "GAMEPAD_EVENT_DEVICE_REMOVED" // Can be dispatched at any time

// eventData -> struct Gamepad_buttonEvent
#define GAMEPAD_EVENT_BUTTON_DOWN     "GAMEPAD_EVENT_BUTTON_DOWN" // Only dispatched when Gamepad_processEvents is called
#define GAMEPAD_EVENT_BUTTON_UP       "GAMEPAD_EVENT_BUTTON_UP" // Only dispatched when Gamepad_processEvents is called

// eventData -> struct Gamepad_axisEvent
#define GAMEPAD_EVENT_AXIS_MOVED      "GAMEPAD_EVENT_AXIS_MOVED" // Only dispatched when Gamepad_processEvents is called

struct Gamepad_buttonEvent {
	// Device that generated the event
	struct Gamepad_device * device;
	
	// Relative time of the event, in seconds
	double timestamp;
	
	// Button being pushed or released
	unsigned int buttonID;
	
	// True if button is down
	bool down;
};

struct Gamepad_axisEvent {
	// Device that generated the event
	struct Gamepad_device * device;
	
	// Relative time of the event, in seconds
	double timestamp;
	
	// Axis being moved
	unsigned int axisID;
	
	// Axis position value, in the range [-1..1]
	float value;
};

struct Gamepad_device {
	// Unique device identifier for application session. If a device is removed and subsequently reattached during the same application session, it will have a new deviceID.
	unsigned int deviceID;
	
	// Human-readable device name
	const char * description;
	
	// USB vendor/product IDs as returned by the driver. Can be used to determine the particular model of device represented.
	int vendorID;
	int productID;
	
	// Number of axis elements belonging to the device
	unsigned int numAxes;
	
	// Number of button elements belonging to the device
	unsigned int numButtons;
	
	// Array[numAxes] of values representing the current state of each axis, in the range [-1..1]
	float * axisStates;
	
	// Array[numButtons] of values representing the current state of each button
	bool * buttonStates;
	
	// Broadcasts GAMEPAD_EVENT_BUTTON_DOWN, GAMEPAD_EVENT_BUTTON_UP, and GAMEPAD_EVENT_AXIS_MOVED
	EventDispatcher * eventDispatcher;
	
	// Platform-specific device data storage; don't mess with it
	void * privateData;
};

/* Initializes gamepad library and detects initial devices. Call this before any other Gamepad_*()
   function, EXCEPT Gamepad_eventDispatcher(). In order to get receive GAMEPAD_EVENT_DEVICE_ATTACHED
   events from devices detected in Gamepad_init(), you must register handlers for those events before
   calling Gamepad_init(). */
void Gamepad_init();

/* Tears down all data structures created by the gamepad library and releases any memory that was
   allocated. It is not necessary to call this function at application termination. */
void Gamepad_shutdown();

/* EventDispatcher used by gamepad library to broadcast GAMEPAD_EVENT_DEVICE_ATTACHED and
   GAMEPAD_EVENT_DEVICE_REMOVED events. */
EventDispatcher * Gamepad_eventDispatcher();

/* Returns the number of currently attached gamepad devices. */
unsigned int Gamepad_numDevices();

/* Returns the specified Gamepad_device struct, or NULL if deviceIndex is out of bounds. */
struct Gamepad_device * Gamepad_deviceAtIndex(unsigned int deviceIndex);

/* Polls for any devices that have been attached since the last call to Gamepad_detectDevices() or
   Gamepad_init(). If any new devices are found, a GAMEPAD_EVENT_DEVICE_ATTACHED event will be
   broadcast via Gamepad_eventDispatcher() for each one. */
void Gamepad_detectDevices();

/* Reads pending input from all attached devices and broadcasts GAMEPAD_EVENT_BUTTON_DOWN,
   GAMEPAD_EVENT_BUTTON_UP, and GAMEPAD_EVENT_AXIS_MOVED events through the eventDispatcher of the
   device that generated the event. */
void Gamepad_processEvents();

#endif
