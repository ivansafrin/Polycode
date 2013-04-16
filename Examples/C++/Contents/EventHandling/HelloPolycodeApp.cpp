#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	  
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	rotateTimer = new Timer(true, 1000);
	rotateTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	Screen *screen = new Screen();			
	image = new ScreenImage("Resources/polycode_logo.png");
	screen->addChild(image);	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == rotateTimer && e->getEventCode() == Timer::EVENT_TRIGGER) {
		image->setRotation(image->getRotation() + 90);
	}
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
