#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	PhysicsScene2D *scene = new PhysicsScene2D(10, 60);
	
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 600,30);
	shape->setColor(0.0,0.0,0.1,1.0);
	shape->setPosition(640/2, 40);
	scene->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, true);	
	
	for(int i=0; i < 200; i++) {
		shape = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 20,5);
		shape->setPitch(rand() % 360);
		shape->setPosition(rand() % 640, rand() % 300);
		scene->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, false);		
	}

}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
