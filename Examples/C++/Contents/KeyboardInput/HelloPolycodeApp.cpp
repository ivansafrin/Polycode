#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();			
	image = new ScreenImage("Resources/polycode_logo.png");
	image->setPositionMode(ScreenEntity::POSITION_CENTER);
	image->setPosition(640/2, 480/2);
	screen->addChild(image);	
	
	rotationSpeed = 0;
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
					case KEY_LEFT:
						rotationSpeed = -200;
					break;
					case KEY_RIGHT:
						rotationSpeed = 200;					
					break;
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_LEFT:
					case KEY_RIGHT:
						rotationSpeed = 0;					
					break;					
				}
			break;			
		}
		
	}
}

bool HelloPolycodeApp::Update() {
	
	Number elapsed = core->getElapsed();
	image->setRotation(image->getRotation() + elapsed * rotationSpeed);
	
    return core->updateAndRender();
}
