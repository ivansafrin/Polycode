#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene();
	mesh = new SceneMesh("Resources/dummy.mesh");
	mesh->loadTexture("Resources/dummy.png");
	scene->addEntity(mesh);
    
	mesh->loadSkeleton("Resources/dummy.skeleton");
	mesh->getSkeleton()->addAnimation("idle", "Resources/idle.anim");
	mesh->getSkeleton()->addAnimation("run", "Resources/run.anim");
	mesh->getSkeleton()->setBaseAnimationByName("idle");
    
	scene->getDefaultCamera()->setPosition(5,5,5);
	scene->getDefaultCamera()->lookAt(Vector3(0,1.0,0));

    blendSinVal = 0.0;
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    
    blendSinVal += core->getElapsed() * 0.5;
    
    mesh->getSkeleton()->playAnimationByName("run", fabs(sin(blendSinVal)));
    
    return core->updateAndRender();
}
