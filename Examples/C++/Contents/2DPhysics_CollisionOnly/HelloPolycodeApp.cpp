#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	screen = new PhysicsScreen(10, 50);
	
	checkShape = new ScreenShape(ScreenShape::SHAPE_RECT, 90,10);
	screen->addCollisionChild(checkShape, PhysicsScreenEntity::ENTITY_RECT);

	
	for(int i=0; i < 50; i++) {
		ScreenShape *shape = new ScreenShape(ScreenShape::SHAPE_RECT, 30,15);
		shape->setRotation(rand() % 360);
		shape->setPosition(rand() % 640, rand() % 480);
		screen->addCollisionChild(shape, PhysicsScreenEntity::ENTITY_RECT);
	}
	
	screen->addEventListener(this, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);	
	screen->addEventListener(this, PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);	
}

void HelloPolycodeApp::handleEvent(Event *e) {
	if(e->getDispatcher() == screen) {
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
	checkShape->setRotation(checkShape->getRotation() + (core->getElapsed() * 100));
    return core->updateAndRender();
}
