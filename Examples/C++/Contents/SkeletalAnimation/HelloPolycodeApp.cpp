#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);

	Scene *scene = new Scene();
	SceneMesh *mesh = new SceneMesh("Resources/ninja.mesh");
	mesh->loadTexture("Resources/ninja.png");
	scene->addEntity(mesh);
	mesh->loadSkeleton("Resources/ninja.skeleton");
	mesh->getSkeleton()->addAnimation("Run", "Resources/run.anim");
	mesh->getSkeleton()->playAnimation("Run");

	scene->getDefaultCamera()->setPosition(25,25,25);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));	

}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
