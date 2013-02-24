#include "HelloPolycodeApp.h"
	
HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

#ifdef __APPLE__
	core = new CocoaCore(view, 640,480,false,false,0,0,90);	  
#else
	core = new SDLCore(view, 640,480,false,false,0,0,90);	  
#endif
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	Screen *screen = new Screen();
	ScreenLabel *label = new ScreenLabel("Click anywhere to play a sound!", 32);
	screen->addChild(label);
		
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	testSound = new Sound("Resources/test.wav");
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		switch(e->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
			testSound->Play();
			break;			
		}
	}	
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
