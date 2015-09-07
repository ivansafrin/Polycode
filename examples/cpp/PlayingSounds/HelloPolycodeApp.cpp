#include "HelloPolycodeApp.h"
	
HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	Scene *scene = new Scene();
	SceneLabel *label = new SceneLabel("Click anywhere to play a sound!", 32);
	scene->addChild(label);
		
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
    return core->updateAndRender();
}
