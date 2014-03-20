#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90, 1, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene(Scene::SCENE_2D);
    scene->getActiveCamera()->setOrthoSize(640, 480);
	for(Number i=0; i < 10; i++) {
		SceneImage *image = new SceneImage("Resources/polycode_logo.png");
		scene->addChild(image);	
		image->setPosition((30*i), 0);
		image->setRoll(45*i);
		image->setScale(1.0-(0.1*i),1.0-(0.1*i));
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
