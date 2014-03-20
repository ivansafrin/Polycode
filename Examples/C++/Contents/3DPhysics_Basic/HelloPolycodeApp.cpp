#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	PhysicsScene *scene = new PhysicsScene();

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10, 10);
	ground->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);

	for(int i=0; i < 100; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));		
		box->setPosition(-2 + (rand() % 4), i*0.5, -2 + (rand() % 4));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}
	
	scene->getDefaultCamera()->setPosition(7,7,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
