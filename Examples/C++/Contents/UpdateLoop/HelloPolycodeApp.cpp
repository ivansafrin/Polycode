#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	  
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene(Scene::SCENE_2D);			
	image = new SceneImage("Resources/polycode_logo.png");
	scene->addChild(image);	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
	image->setRoll(image->getRoll()+(elapsed*100));
    return core->updateAndRender();
}
