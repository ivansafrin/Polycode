#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	scene = new PhysicsScene2D(0.5, 50);
	lastEntity = NULL;
	
	for(int i=0; i < 50; i++) {
		ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 30,15);
		shape->setRoll(rand() % 360);
		shape->setPosition(-640/2 + rand() % 640, 480/2 - rand() % 480);
		scene->addCollisionChild(shape, PhysicsScene2DEntity::ENTITY_RECT);
	}
	
}


HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	if(lastEntity)
		lastEntity->setColor(1.0, 1.0, 1.0, 1.0);	
	Vector2 mouse = core->getInput()->getMousePosition();
	SceneEntity * entity = scene->getEntityAtPosition(mouse.x-680/2+20, -mouse.y+480/2);
	if(entity) {
		entity->setColor(1.0, 0.0, 0.0, 1.0);
		lastEntity = entity;
	}
    return core->updateAndRender();
}
