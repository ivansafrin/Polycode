#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	PhysicsScene2D *scene = new PhysicsScene2D(10, 50);
	
	checkShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 90,10);
	scene->addCollisionChild(checkShape, PhysicsScreenEntity::ENTITY_RECT);

	
	for(int i=0; i < 50; i++) {
		ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 30,15);
		shape->setRoll(rand() % 360);
		shape->setPosition(rand() % 640, rand() % 480);
		scene->addCollisionChild(shape, PhysicsScreenEntity::ENTITY_RECT);
	}
	
	scene->addEventListener(this, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);	
	scene->addEventListener(this, PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);	
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == scene) {
		PhysicsScreenEvent *pe = (PhysicsScreenEvent*)e;	
		switch(e->getEventCode()) {
			case PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION:
				if(pe->entity1 == checkShape || pe->entity2 == checkShape) {
					pe->entity1->setColor(1.0f, 0.0f, 0.0f, 1.0f);
					pe->entity2->setColor(1.0f, 0.0f, 0.0f, 1.0f);
				}
			break;
			case PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION:
				pe->entity1->setColor(1.0f, 1.0f, 1.0f, 1.0f);
				pe->entity2->setColor(1.0f, 1.0f, 1.0f, 1.0f);				
			break;
			
		}
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	Vector2 mouse = core->getInput()->getMousePosition();
	checkShape->setPosition(mouse.x, mouse.y);
	checkShape->setRoll(checkShape->getRoll() + (core->getElapsed() * 100));
    return core->updateAndRender();
}
