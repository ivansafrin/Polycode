#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	PhysicsScene2D *scene = new PhysicsScene2D(10, 60);
	
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 600,30);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(0, -480/2+40);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	for(int i=0; i < 200; i++) {
		shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 20,5);
		shape->setRoll(rand() % 360);
		shape->setPosition(-640/2 + rand() % 640, 480/2 - rand() % 300);
		scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);		
	}

}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
