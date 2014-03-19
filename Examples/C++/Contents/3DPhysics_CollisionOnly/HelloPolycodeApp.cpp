#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	scene = new CollisionScene();

	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10, 10);
	ground->loadTexture("Resources/green_texture.png");
	scene->addEntity(ground);

	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5,0.5,0.5);
	box->loadTexture("Resources/pink_texture.png");
	box->setPosition(0,1,0);
	scene->addCollisionChild(box, CollisionEntity::SHAPE_BOX);

	bigBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 2,2,2);
	bigBox->loadTexture("Resources/pink_texture.png");
	bigBox->setColor(0.0,1.0,1.0,0.5);
	bigBox->setPosition(0,1,0);
	scene->addCollisionChild(bigBox, CollisionEntity::SHAPE_BOX);

	
	scene->getDefaultCamera()->setPosition(7,7,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	
	swingValue = 0;
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
	swingValue += elapsed;
	box->setPosition(sin(swingValue) * 5,1,0);	
	
	CollisionResult res = scene->testCollision(box, bigBox);
	if(res.collided) {
		bigBox->setColor(1.0,1.0,0.0,0.5);		
	} else {
		bigBox->setColor(0.0,1.0,1.0,0.5);	
	}
	
    return core->updateAndRender();
}
