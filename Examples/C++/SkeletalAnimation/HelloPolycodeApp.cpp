#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);

	Scene *scene = new Scene();
	SceneMesh *mesh = new SceneMesh("ninja.mesh");
	mesh->loadTexture("ninja.png");
	scene->addEntity(mesh);
	mesh->loadSkeleton("ninja.skeleton");
	mesh->getSkeleton()->addAnimation("Run", "run.anim");
	mesh->getSkeleton()->playAnimation("Run");

	scene->getDefaultCamera()->setPosition(25,25,25);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));	

}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
