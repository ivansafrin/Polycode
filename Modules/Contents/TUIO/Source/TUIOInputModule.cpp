
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
	
	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	events.push_back(event);					
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);
}

void TUIOInputModule::refresh(TuioTime frameTime) {
}	

void TUIOInputModule::Update(Number elapsed) {

	CoreServices::getInstance()->getCore()->lockMutex(eventMutex);
	for(int i=0; i < events.size(); i++) {
		for(int j=0; j < events[i].touches.size(); j++) {
			events[i].touches[j].position.x = events[i].touches[j].position.x * CoreServices::getInstance()->getCore()->getXRes();
			events[i].touches[j].position.y = events[i].touches[j].position.y * CoreServices::getInstance()->getCore()->getYRes();			
		}
		switch(events[i].type) {
			case InputEvent::EVENT_TOUCHES_BEGAN:
				CoreServices::getInstance()->getCore()->getInput()->touchesBegan(events[i].touches);
			break;
			case InputEvent::EVENT_TOUCHES_MOVED:
				CoreServices::getInstance()->getCore()->getInput()->touchesMoved(events[i].touches);
			break;
			case InputEvent::EVENT_TOUCHES_ENDED:
				CoreServices::getInstance()->getCore()->getInput()->touchesEnded(events[i].touches);			
			break;			
		}
	}
	events.clear();
	CoreServices::getInstance()->getCore()->unlockMutex(eventMutex);	
}