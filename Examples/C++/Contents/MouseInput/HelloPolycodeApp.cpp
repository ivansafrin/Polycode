#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene(Scene::SCENE_2D);			
	image = new SceneImage("Resources/polycode_logo.png");
	scene->addChild(image);	
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		switch(e->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				image->setPosition(inputEvent->mousePosition.x-680/2+20,
						-inputEvent->mousePosition.y+480/2);
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
    return core->updateAndRender();
}
