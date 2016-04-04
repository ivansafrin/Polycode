
#include "polycode/core/PolyThreaded.h"
#include "polycode/core/PolyCore.h"

using namespace Polycode;

Threaded::Threaded() : EventDispatcher() {
	core = NULL;
	threadRunning = true;
	scheduledForRemoval = false;
}

Threaded::~Threaded() {
	core->removeThread(this);
}

void Threaded::killThread() {
	threadRunning = false;
}

void Threaded::runThread(){
	while(threadRunning) {
		updateThread();
	}
}

void Threaded::dispatchEvent(Event *event, int eventCode) {
	core->lockMutex(eventMutex);
	event->setEventCode(eventCode);
	eventQueue.push_back(event);
	core->unlockMutex(eventMutex);	
}
		
void Threaded::dispatchEventNoDelete(Event *event, int eventCode) {
	core->lockMutex(eventMutex);
	event->setEventCode(eventCode);
	event->deleteOnDispatch = false;
	eventQueue.push_back(event);	
	core->unlockMutex(eventMutex);			
}
