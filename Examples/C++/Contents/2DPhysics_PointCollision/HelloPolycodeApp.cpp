#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

#ifdef __APPLE__
	core = new CocoaCore(view, 640,480,false,0,90);	  
#else
	core = new SDLCore(view, 640,480,false,0,90);	  
#endif
	
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	screen = new PhysicsScreen(10, 50);
	lastEntity = NULL;
	
	for(int i=0; i < 50; i++) {
		ScreenShape *shape = new ScreenShape(ScreenShape::SHAPE_RECT, 30,15);
		shape->setRotation(rand() % 360);
		shape->setPosition(rand() % 640, rand() % 480);
		screen->addCollisionChild(shape, PhysicsScreenEntity::ENTITY_RECT);
	}
	
}


HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	if(lastEntity)
		lastEntity->setColor(1.0, 1.0, 1.0, 1.0);	
	Vector2 mouse = core->getInput()->getMousePosition();
	ScreenEntity * entity = screen->getEntityAtPosition(mouse.x, mouse.y);
	if(entity) {
		entity->setColor(1.0, 0.0, 0.0, 1.0);
		lastEntity = entity;
	}
    return core->Update();
}