#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	scene = new Scene(Scene::SCENE_2D);
    scene->getActiveCamera()->setOrthoSize(640,480);
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
            {
                Ray ray =scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(), inputEvent->getMousePosition());
                image->setPosition(ray.origin.x, ray.origin.y);
            }
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
