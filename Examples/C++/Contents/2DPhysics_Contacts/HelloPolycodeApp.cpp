#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	scene = new PhysicsScene2D(0.1, 60);
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1.0,0.05);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(0, -0.3);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, true);
	
	for(int i=0; i < 50; i++) {
		shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.08,0.02);
		shape->setRoll(rand() % 360);
        shape->setColor(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER, 1.0);
		shape->setPosition(-0.3 + (RANDOM_NUMBER*0.6), RANDOM_NUMBER);
		scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	}
    
	collisionSound = new Sound("Resources/hit.wav");
	scene->addEventListener(this, PhysicsScene2DEvent::EVENT_SOLVE_SHAPE_COLLISION);
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == scene) {
		switch(e->getEventCode()) {
			case PhysicsScene2DEvent::EVENT_SOLVE_SHAPE_COLLISION:
				PhysicsScene2DEvent *pe = (PhysicsScene2DEvent*)e;
				if(pe->impactStrength > 1.0)
					collisionSound->Play();
			break;
		}
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
