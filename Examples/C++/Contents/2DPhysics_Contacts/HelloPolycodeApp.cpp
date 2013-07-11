#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	screen = new PhysicsScreen(10, 60);		
	ScreenShape *shape = new ScreenShape(ScreenShape::SHAPE_RECT, 600,30);
	shape->setColor(0.0,0.0,0.0,1.0);
	shape->setPosition(640/2, 400);
	screen->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, true);	
	
	for(int i=0; i < 50; i++) {
		shape = new ScreenShape(ScreenShape::SHAPE_RECT, 20,5);
		shape->setRotation(rand() % 360);
		shape->setPosition(rand() % 640, rand() % 300);
		screen->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, false);		
	}
	collisionSound = new Sound("Resources/hit.wav");
	screen->addEventListener(this, PhysicsScreenEvent::EVENT_SOLVE_SHAPE_COLLISION);
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == screen) {
		switch(e->getEventCode()) {
			case PhysicsScreenEvent::EVENT_SOLVE_SHAPE_COLLISION:
				PhysicsScreenEvent *pe = (PhysicsScreenEvent*)e;
				if(pe->impactStrength > 5)
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
