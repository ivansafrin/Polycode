#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

#ifdef __APPLE__
	core = new CocoaCore(view, 640,480,false,0,90);	  
#else
	core = new SDLCore(view, 640,480,false,0,90);	  
#endif

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();			
	image = new ScreenImage("Resources/polycode_logo.png");
	image->setPositionMode(ScreenEntity::POSITION_CENTER);
	screen->addChild(image);	
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
}

void HelloPolycodeApp::handleEvent(Event *e) {
	
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		switch(e->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				image->setPosition(inputEvent->mousePosition.x,
						   inputEvent->mousePosition.y);
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				image->setColor(1,0,0,1);
			break;			
			case InputEvent::EVENT_MOUSEUP:
				image->setColor(1,1,1,1);	
			break;						
		}
	}
	
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
