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

#include "gamepad/Gamepad.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

struct Gamepad_devicePrivate {
	pthread_t thread;
	int fd;
	char * path;
	int buttonMap[KEY_CNT - BTN_MISC];
	int axisMap[ABS_CNT];
	struct input_absinfo axisInfo[ABS_CNT];
};

struct Gamepad_queuedEvent {
	EventDispatcher * dispatcher;
	const char * eventType;
	void * eventData;
};

static struct Gamepad_device ** devices = NULL;
static unsigned int numDevices = 0;
static unsigned int nextDeviceID = 0;
static pthread_mutex_t devicesMutex;

static struct Gamepad_queuedEvent * eventQueue = NULL;
static size_t eventQueueSize = 0;
static size_t eventCount = 0;
static pthread_mutex_t eventQueueMutex;

static EventDispatcher * eventDispatcher = NULL;
static bool inited = false;

#define test_bit(bitIndex, array) \
	((array[(bitIndex) / (sizeof(int) * 8)] >> ((bitIndex) % (sizeof(int) * 8))) & 0x1)

static char ** findGamepadPaths(unsigned int * outNumGamepads) {
	DIR * dev_input;
	struct dirent * entity;
	unsigned int numGamepads = 0;
	char ** gamepadDevs = NULL;
	unsigned int charsConsumed;
	int num;
	int fd;
	int evCapBits[(EV_CNT - 1) / sizeof(int) * 8 + 1];
	int evKeyBits[(KEY_CNT - 1) / sizeof(int) * 8 + 1];
	int evAbsBits[(ABS_CNT - 1) / sizeof(int) * 8 + 1];
	char fileName[PATH_MAX];
	
	dev_input = opendir("/dev/input");
	if (dev_input != NULL) {
		for (entity = readdir(dev_input); entity != NULL; entity = readdir(dev_input)) {
			charsConsumed = 0;
			if (sscanf(entity->d_name, "event%d%n", &num, &charsConsumed) && charsConsumed == strlen(entity->d_name)) {
				snprintf(fileName, PATH_MAX, "/dev/input/%s", entity->d_name);
				fd = open(fileName, O_RDONLY, 0);
				memset(evCapBits, 0, sizeof(evCapBits));
				memset(evKeyBits, 0, sizeof(evKeyBits));
				memset(evAbsBits, 0, sizeof(evAbsBits));
				if (ioctl(fd, EVIOCGBIT(0, sizeof(evCapBits)), evCapBits) < 0 ||
				    ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(evKeyBits)), evKeyBits) < 0 ||
				    ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(evAbsBits)), evAbsBits) < 0) {
					close(fd);
					continue;
				}
				if (!test_bit(EV_KEY, evCapBits) || !test_bit(EV_ABS, evCapBits) ||
				    !test_bit(ABS_X, evAbsBits) || !test_bit(ABS_Y, evAbsBits) ||
				    (!test_bit(BTN_TRIGGER, evKeyBits) && !test_bit(BTN_A, evKeyBits) && !test_bit(BTN_1, evKeyBits))) {
					close(fd);
					continue;
				}
				close(fd);
				
				numGamepads++;
				gamepadDevs = realloc(gamepadDevs, sizeof(char *) * numGamepads);
				gamepadDevs[numGamepads - 1] = malloc(strlen(fileName) + 1);
				strcpy(gamepadDevs[numGamepads - 1], fileName);
			}
		}
		closedir(dev_input);
	}
	
	*outNumGamepads = numGamepads;
	return gamepadDevs;
}

void Gamepad_init() {
	if (!inited) {
		pthread_mutex_init(&devicesMutex, NULL);
		pthread_mutex_init(&eventQueueMutex, NULL);
		inited = true;
		Gamepad_detectDevices();
	}
}

static void disposeDevice(struct Gamepad_device * device) {
	device->eventDispatcher->dispose(device->eventDispatcher);
	
	close(((struct Gamepad_devicePrivate *) device->privateData)->fd);
	free(((struct Gamepad_devicePrivate *) device->privateData)->path);
	free(device->privateData);
	
	free((void *) device->description);
	free(device->axisStates);
	free(device->buttonStates);
	free(device->eventDispatcher);
	
	free(device);
}

void Gamepad_shutdown() {
	if (inited) {
		unsigned int eventIndex;
		unsigned int devicesLeft;
		unsigned int gamepadIndex;
		
		do {
			pthread_mutex_lock(&devicesMutex);
			devicesLeft = numDevices;
			if (devicesLeft > 0) {
				pthread_t thread;
				
				thread = ((struct Gamepad_devicePrivate *) devices[0]->privateData)->thread;
				pthread_cancel(thread);
				pthread_join(thread, NULL);
				
				numDevices--;
				for (gamepadIndex = 0; gamepadIndex < numDevices; gamepadIndex++) {
					devices[gamepadIndex] = devices[gamepadIndex + 1];
				}
			}
			pthread_mutex_unlock(&devicesMutex);
		} while (devicesLeft > 0);
		
		pthread_mutex_destroy(&devicesMutex);
		pthread_mutex_destroy(&eventQueueMutex);
		free(devices);
		devices = NULL;
		
		for (eventIndex = 0; eventIndex < eventCount; eventIndex++) {
			if (!strcmp(eventQueue[eventIndex].eventType, GAMEPAD_EVENT_DEVICE_REMOVED)) {
				disposeDevice(eventQueue[eventIndex].eventData);
			}
		}
		
		eventQueueSize = 0;
		eventCount = 0;
		free(eventQueue);
		eventQueue = NULL;
		
		if (eventDispatcher != NULL) {
			eventDispatcher->dispose(eventDispatcher);
			free(eventDispatcher);
			eventDispatcher = NULL;
		}
		
		inited = false;
	}
}

EventDispatcher * Gamepad_eventDispatcher() {
	if (eventDispatcher == NULL) {
		eventDispatcher = EventDispatcher_create(NULL);
	}
	return eventDispatcher;
}

unsigned int Gamepad_numDevices() {
	unsigned int result;
	
	pthread_mutex_lock(&devicesMutex);
	result = numDevices;
	pthread_mutex_unlock(&devicesMutex);
	return result;
}

struct Gamepad_device * Gamepad_deviceAtIndex(unsigned int deviceIndex) {
	struct Gamepad_device * result;	
	
	pthread_mutex_lock(&devicesMutex);
	if (deviceIndex >= numDevices) {
		result = NULL;
	} else {
		result = devices[deviceIndex];
	}
	pthread_mutex_unlock(&devicesMutex);
	
	return result;
}

static void queueEvent(EventDispatcher * dispatcher, const char * eventType, void * eventData) {
	struct Gamepad_queuedEvent queuedEvent;
	
	queuedEvent.dispatcher = dispatcher;
	queuedEvent.eventType = eventType;
	queuedEvent.eventData = eventData;
	
	pthread_mutex_lock(&eventQueueMutex);
	if (eventCount >= eventQueueSize) {
		eventQueueSize = eventQueueSize == 0 ? 1 : eventQueueSize * 2;
		eventQueue = realloc(eventQueue, sizeof(struct Gamepad_queuedEvent) * eventQueueSize);
	}
	eventQueue[eventCount++] = queuedEvent;
	pthread_mutex_unlock(&eventQueueMutex);
}

static void queueAxisEvent(struct Gamepad_device * device, double timestamp, unsigned int axisID, float value) {
	struct Gamepad_axisEvent * axisEvent;
	
	axisEvent = malloc(sizeof(struct Gamepad_axisEvent));
	axisEvent->device = device;
	axisEvent->timestamp = timestamp;
	axisEvent->axisID = axisID;
	axisEvent->value = value;
	
	queueEvent(device->eventDispatcher, GAMEPAD_EVENT_AXIS_MOVED, axisEvent);
}

static void queueButtonEvent(struct Gamepad_device * device, double timestamp, unsigned int buttonID, bool down) {
	struct Gamepad_buttonEvent * buttonEvent;
	
	buttonEvent = malloc(sizeof(struct Gamepad_buttonEvent));
	buttonEvent->device = device;
	buttonEvent->timestamp = timestamp;
	buttonEvent->buttonID = buttonID;
	buttonEvent->down = down;
	
	queueEvent(device->eventDispatcher, down ? GAMEPAD_EVENT_BUTTON_DOWN : GAMEPAD_EVENT_BUTTON_UP, buttonEvent);
}

static void * deviceThread(void * context) {
	unsigned int gamepadIndex;
	struct Gamepad_device * device;
	struct Gamepad_devicePrivate * devicePrivate;
	struct input_event event;
	
	device = context;
	devicePrivate = device->privateData;
	
	while (read(devicePrivate->fd, &event, sizeof(struct input_event)) > 0) {
		if (event.type == EV_ABS) {
			float value;
			
			if (event.code > ABS_MAX || devicePrivate->axisMap[event.code] == -1) {
				continue;
			}
			
			value = (event.value - devicePrivate->axisInfo[event.code].minimum) / (float) (devicePrivate->axisInfo[event.code].maximum - devicePrivate->axisInfo[event.code].minimum) * 2.0f - 1.0f;
			queueAxisEvent(device,
			               event.time.tv_sec + event.time.tv_usec * 0.000001,
			               devicePrivate->axisMap[event.code],
			               value);
			
			device->axisStates[devicePrivate->axisMap[event.code]] = value;
			
		} else if (event.type == EV_KEY) {
			if (event.code < BTN_MISC || event.code > KEY_MAX || devicePrivate->buttonMap[event.code - BTN_MISC] == -1) {
				continue;
			}
			
			queueButtonEvent(device,
			                 event.time.tv_sec + event.time.tv_usec * 0.000001,
			                 devicePrivate->buttonMap[event.code - BTN_MISC],
			                 !!event.value);
			
			device->buttonStates[devicePrivate->buttonMap[event.code - BTN_MISC]] = !!event.value;
		}
	}
	
	queueEvent(eventDispatcher, GAMEPAD_EVENT_DEVICE_REMOVED, device);
	
	pthread_mutex_lock(&devicesMutex);
	for (gamepadIndex = 0; gamepadIndex < numDevices; gamepadIndex++) {
		if (devices[gamepadIndex] == device) {
			unsigned int gamepadIndex2;
			
			numDevices--;
			for (gamepadIndex2 = gamepadIndex; gamepadIndex2 < numDevices; gamepadIndex2++) {
				devices[gamepadIndex2] = devices[gamepadIndex2 + 1];
			}
			gamepadIndex--;
		}
	}
	pthread_mutex_unlock(&devicesMutex);
	
	return NULL;
}

void Gamepad_detectDevices() {
	unsigned int numPaths;
	char ** gamepadPaths;
	bool duplicate;
	unsigned int pathIndex, gamepadIndex;
	struct stat statBuf;
	struct Gamepad_device * deviceRecord;
	struct Gamepad_devicePrivate * deviceRecordPrivate;
	int fd;
	char name[128];
	char * description;
	int evKeyBits[(KEY_CNT - 1) / sizeof(int) * 8 + 1];
	int evAbsBits[(ABS_CNT - 1) / sizeof(int) * 8 + 1];
	int bit;
	struct input_id id;
	
	if (!inited) {
		return;
	}
	
	gamepadPaths = findGamepadPaths(&numPaths);
	
	pthread_mutex_lock(&devicesMutex);
	for (pathIndex = 0; pathIndex < numPaths; pathIndex++) {
		duplicate = false;
		for (gamepadIndex = 0; gamepadIndex < numDevices; gamepadIndex++) {
			if (!strcmp(((struct Gamepad_devicePrivate *) devices[gamepadIndex]->privateData)->path, gamepadPaths[pathIndex])) {
				duplicate = true;
				break;
			}
		}
		if (duplicate) {
			free(gamepadPaths[pathIndex]);
			continue;
		}
		
		if (!stat(gamepadPaths[pathIndex], &statBuf)) {
			deviceRecord = malloc(sizeof(struct Gamepad_device));
			deviceRecord->deviceID = nextDeviceID++;
			deviceRecord->eventDispatcher = EventDispatcher_create(deviceRecord);
			devices = realloc(devices, sizeof(struct Gamepad_device *) * (numDevices + 1));
			devices[numDevices++] = deviceRecord;
			
			fd = open(gamepadPaths[pathIndex], O_RDONLY, 0);
			
			deviceRecordPrivate = malloc(sizeof(struct Gamepad_devicePrivate));
			deviceRecordPrivate->fd = fd;
			deviceRecordPrivate->path = gamepadPaths[pathIndex];
			memset(deviceRecordPrivate->buttonMap, 0xFF, sizeof(deviceRecordPrivate->buttonMap));
			memset(deviceRecordPrivate->axisMap, 0xFF, sizeof(deviceRecordPrivate->axisMap));
			deviceRecord->privateData = deviceRecordPrivate;
			
			if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) > 0) {
				description = malloc(strlen(name + 1));
				strcpy(description, name);
			} else {
				description = malloc(strlen(gamepadPaths[pathIndex] + 1));
				strcpy(description, gamepadPaths[pathIndex]);
			}
			deviceRecord->description = description;
			
			if (!ioctl(fd, EVIOCGID, &id)) {
				deviceRecord->vendorID = id.vendor;
				deviceRecord->productID = id.product;
			} else {
				deviceRecord->vendorID = deviceRecord->productID = 0;
			}
			
			memset(evKeyBits, 0, sizeof(evKeyBits));
			memset(evAbsBits, 0, sizeof(evAbsBits));
			ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(evKeyBits)), evKeyBits);
			ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(evAbsBits)), evAbsBits);
			
			deviceRecord->numAxes = 0;
			for (bit = 0; bit < ABS_CNT; bit++) {
				if (test_bit(bit, evAbsBits)) {
					if (ioctl(fd, EVIOCGABS(bit), &deviceRecordPrivate->axisInfo[bit]) < 0 ||
					    deviceRecordPrivate->axisInfo[bit].minimum == deviceRecordPrivate->axisInfo[bit].maximum) {
						continue;
					}
					deviceRecordPrivate->axisMap[bit] = deviceRecord->numAxes;
					deviceRecord->numAxes++;
				}
			}
			deviceRecord->numButtons = 0;
			for (bit = BTN_MISC; bit < KEY_CNT; bit++) {
				if (test_bit(bit, evKeyBits)) {
					deviceRecordPrivate->buttonMap[bit - BTN_MISC] = deviceRecord->numButtons;
					deviceRecord->numButtons++;
				}
			}
			
			deviceRecord->axisStates = calloc(sizeof(float), deviceRecord->numAxes);
			deviceRecord->buttonStates = calloc(sizeof(bool), deviceRecord->numButtons);
			
			Gamepad_eventDispatcher()->dispatchEvent(Gamepad_eventDispatcher(), GAMEPAD_EVENT_DEVICE_ATTACHED, deviceRecord);
			
			pthread_create(&deviceRecordPrivate->thread, NULL, deviceThread, deviceRecord);
		}
	}
	pthread_mutex_unlock(&devicesMutex);
}

void Gamepad_processEvents() {
	unsigned int eventIndex;	
	
	if (!inited) {
		return;
	}
	
	pthread_mutex_lock(&eventQueueMutex);
	for (eventIndex = 0; eventIndex < eventCount; eventIndex++) {
		eventQueue[eventIndex].dispatcher->dispatchEvent(eventQueue[eventIndex].dispatcher, eventQueue[eventIndex].eventType, eventQueue[eventIndex].eventData);
		if (!strcmp(eventQueue[eventIndex].eventType, GAMEPAD_EVENT_DEVICE_REMOVED)) {
			disposeDevice(eventQueue[eventIndex].eventData);
		}
	}
	eventCount = 0;
	pthread_mutex_unlock(&eventQueueMutex);
}

