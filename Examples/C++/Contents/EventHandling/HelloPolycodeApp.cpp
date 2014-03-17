#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	  
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	rotateTimer = new Timer(true, 1000);
	rotateTimer->addEventListener(this, Timer::EVENT_TRIGGER);

	Scene *scene = new Scene(Scene::SCENE_2D);			
	image = new SceneImage("Resources/polycode_logo.png");
	scene->addChild(image);	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == rotateTimer && e->getEventCode() == Timer::EVENT_TRIGGER) {
		image->setRoll(image->getRoll() + 90);
	}
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
