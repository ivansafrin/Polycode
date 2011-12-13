#include "PolyStemGamepad.h"

extern "C" {
bool onButtonDown(void * sender, const char * eventID, void * eventData, void * context) {
	struct Gamepad_buttonEvent * event;	
	event = (Gamepad_buttonEvent*)eventData;
	StemGamepadController *controller = (StemGamepadController*) context;
	controller->coreInput->joystickButtonDown(event->buttonID, event->device->deviceID);	
	return true;
}

bool onButtonUp(void * sender, const char * eventID, void * eventData, void * context) {
	struct Gamepad_buttonEvent * event;
	event = (Gamepad_buttonEvent *)eventData;	
	StemGamepadController *controller = (StemGamepadController*) context;
	controller->coreInput->joystickButtonUp(event->buttonID, event->device->deviceID);
	return true;
}

bool onAxisMoved(void * sender, const char * eventID, void * eventData, void * context) {
	struct Gamepad_axisEvent * event;	
	event = (Gamepad_axisEvent *)eventData;
	StemGamepadController *controller = (StemGamepadController*) context;
	controller->coreInput->joystickAxisMoved(event->axisID, event->value, event->device->deviceID);
	return true;
}

bool onDeviceAttached(void * sender, const char * eventID, void * eventData, void * context) {
	struct Gamepad_device * device;	
	device = (Gamepad_device*) eventData;
	
	StemGamepadController *controller = (StemGamepadController*) context;
	controller->coreInput->addJoystick(device->deviceID);

	device->eventDispatcher->registerForEvent(device->eventDispatcher, GAMEPAD_EVENT_BUTTON_DOWN, onButtonDown, controller);
	device->eventDispatcher->registerForEvent(device->eventDispatcher, GAMEPAD_EVENT_BUTTON_UP, onButtonUp, controller);
	device->eventDispatcher->registerForEvent(device->eventDispatcher, GAMEPAD_EVENT_AXIS_MOVED, onAxisMoved, controller);

	return true;
}

bool onDeviceRemoved(void * sender, const char * eventID, void * eventData, void * context) {
	struct Gamepad_device * device;	
	device = (Gamepad_device *)eventData;
	StemGamepadController *controller = (StemGamepadController*) context;
	controller->coreInput->removeJoystick(device->deviceID);	
	return true;
}

StemGamepadController::StemGamepadController(Polycode::CoreInput *coreInput) {
	this->coreInput = coreInput;
	Gamepad_eventDispatcher()->registerForEvent(Gamepad_eventDispatcher(), GAMEPAD_EVENT_DEVICE_ATTACHED, onDeviceAttached, this);
	Gamepad_eventDispatcher()->registerForEvent(Gamepad_eventDispatcher(), GAMEPAD_EVENT_DEVICE_REMOVED, onDeviceRemoved, this);
	Gamepad_init();
	iterationsToNextPoll = POLL_ITERATION_INTERVAL;
}

StemGamepadController::~StemGamepadController() {

}

void StemGamepadController::Update() {
	iterationsToNextPoll--;
	if (iterationsToNextPoll == 0) {
		Gamepad_detectDevices();
		iterationsToNextPoll = POLL_ITERATION_INTERVAL;
	}
	Gamepad_processEvents();
	
}
}