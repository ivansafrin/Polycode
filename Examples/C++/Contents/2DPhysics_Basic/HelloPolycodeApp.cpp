#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	PhysicsScene2D *scene = new PhysicsScene2D(0.1, 60);	
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1.0,0.05);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(0, -0.3);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, true);	
	
	for(int i=0; i < 200; i++) {
		shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.08,0.02);
		shape->setRoll(rand() % 360);
        shape->setColor(RANDOM_NUMBER, RANDOM_NUMBER, RANDOM_NUMBER, 1.0);
		shape->setPosition(-0.3 + (RANDOM_NUMBER*0.6), RANDOM_NUMBER);
		scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
