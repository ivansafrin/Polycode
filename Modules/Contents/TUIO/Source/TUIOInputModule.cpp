
#include "TUIOInputModule.h"
#include <Polycode.h>


TUIOInputModule::TUIOInputModule(int port) : PolycodeModule(), TuioListener() {
	tuioClient = new TuioClient(port);
	tuioClient->addTuioListener(this);
	tuioClient->connect();
	
	eventMutex = CoreServices::getInstance()->getCore()->createMutex();
	_requiresUpdate = true;

}

TUIOInputModule::~TUIOInputModule() {
	tuioClient->removeAllTuioListeners();
	tuioClient->disconnect();
	delete tuioClient;
	delete eventMutex;
}

void TUIOInputModule::addTuioObject(TuioObject *tobj) {
}

void TUIOInputModule::updateTuioObject(TuioObject *tobj) {
}

void TUIOInputModule::removeTuioObject(TuioObject *tobj) {
}

void TUIOInputModule::addTuioCursor(TuioCursor *tcur) {
	std::vector<TouchInfo> touches;	
	std::list<TuioCursor*> cursorList = tuioClient->getTuioCursors();
	tuioClient->lockCursorList();
	for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter!=cursorList.end(); iter++) {
			TuioCursor *tuioCursor = (*iter);	
			TouchInfo touch;	
			touch.position.x = tuioCursor->getX();
			touch.position.y = tuioCursor->getY();
			touch.id= tuioCursor->getCursorID();
			touches.push_back(touch);
	}
	tuioClient->unlockCursorList();	
	TUIOEvent event;
	event.type = InputEvent::EVENT_TOUCHES_BEGAN;
	event.touches = touches;
	
	event.touch.position.x = tcur->getX();
	event.touch.position.y = tcur->getY();
	event.touch.id = tcur->getCursorID();
	
	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	events.push_back(event);					
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);
}

void TUIOInputModule::updateTuioCursor(TuioCursor *tcur) {
	std::vector<TouchInfo> touches;	
	std::list<TuioCursor*> cursorList = tuioClient->getTuioCursors();
	tuioClient->lockCursorList();
	for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter!=cursorList.end(); iter++) {
			TuioCursor *tuioCursor = (*iter);	
			TouchInfo touch;	
			touch.position.x = tuioCursor->getX();
			touch.position.y = tuioCursor->getY();
			touch.id= tuioCursor->getCursorID();			
			touches.push_back(touch);
	}
	tuioClient->unlockCursorList();	
	TUIOEvent event;
	event.type = InputEvent::EVENT_TOUCHES_MOVED;
	event.touches = touches;
	
	event.touch.position.x = tcur->getX();
	event.touch.position.y = tcur->getY();
	event.touch.id = tcur->getCursorID();
		
	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	events.push_back(event);					
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);
}

void TUIOInputModule::removeTuioCursor(TuioCursor *tcur) {
	std::vector<TouchInfo> touches;	
	std::list<TuioCursor*> cursorList = tuioClient->getTuioCursors();
	tuioClient->lockCursorList();
	for (std::list<TuioCursor*>::iterator iter = cursorList.begin(); iter!=cursorList.end(); iter++) {
			TuioCursor *tuioCursor = (*iter);	
			TouchInfo touch;	
			touch.position.x = tuioCursor->getX();
			touch.position.y = tuioCursor->getY();
			touch.id= tuioCursor->getCursorID();			
			touches.push_back(touch);
	}
	tuioClient->unlockCursorList();
	TUIOEvent event;
	event.type = InputEvent::EVENT_TOUCHES_ENDED;
	event.touches = touches;
	
	event.touch.position.x = tcur->getX();
	event.touch.position.y = tcur->getY();
	event.touch.id = tcur->getCursorID();	
	
	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	events.push_back(event);					
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);
}

void TUIOInputModule::refresh(TuioTime frameTime) {
}	

void TUIOInputModule::Update(Number elapsed) {

	Core *core = CoreServices::getInstance()->getCore();

	core->lockMutex(core->eventMutex);	
	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	for(int i=0; i < events.size(); i++) {
		for(int j=0; j < events[i].touches.size(); j++) {
			events[i].touches[j].position.x = events[i].touches[j].position.x * core->getXRes();
			events[i].touches[j].position.y = events[i].touches[j].position.y * core->getYRes();			
		}
		events[i].touch.position.x = events[i].touch.position.x * core->getXRes();
		events[i].touch.position.y = events[i].touch.position.y * core->getYRes();
		
		switch(events[i].type) {
			case InputEvent::EVENT_TOUCHES_BEGAN:
				CoreServices::getInstance()->getCore()->getInput()->touchesBegan(events[i].touch, events[i].touches, core->getTicks());
			break;
			case InputEvent::EVENT_TOUCHES_MOVED:
				CoreServices::getInstance()->getCore()->getInput()->touchesMoved(events[i].touch, events[i].touches, core->getTicks());
			break;
			case InputEvent::EVENT_TOUCHES_ENDED:
				CoreServices::getInstance()->getCore()->getInput()->touchesEnded(events[i].touch, events[i].touches, core->getTicks());			
			break;			
		}
	}
	events.clear();
	core->unlockMutex(core->eventMutex);	
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);	
}