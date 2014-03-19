#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90,0, true);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	scene = new PhysicsScene2D(0.01, 50);
	lastEntity = NULL;
	
	for(int i=0; i < 50; i++) {
		ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.1,0.02);
		shape->setRoll(rand() % 360);
		shape->setPosition(-0.5 + RANDOM_NUMBER, -0.5 + RANDOM_NUMBER);
		scene->addCollisionChild(shape, PhysicsScene2DEntity::ENTITY_RECT);
	}
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	if(lastEntity)
		lastEntity->setColor(1.0, 1.0, 1.0, 1.0);	
	Vector2 mouse = core->getInput()->getMousePosition();
    Ray ray = scene->projectRayFromCameraAndViewportCoordinate(scene->getActiveCamera(), mouse);
    
	SceneEntity * entity = scene->getEntityAtPosition(ray.origin.x, ray.origin.y);
	if(entity) {
		entity->setColor(1.0, 0.0, 0.0, 1.0);
		lastEntity = entity;
	}
    return core->updateAndRender();
}
