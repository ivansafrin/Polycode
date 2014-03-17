#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	PhysicsScene2D *scene = new PhysicsScene2D(10, 50);

	ScenePrimitive *ceiling = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 640, 20);
	ceiling->setColor(0.0, 0.0, 0.0, 1.0);
	ceiling->setPosition(0, 480/2-10);
	scene->addPhysicsChild(ceiling, PhysicsScene2DEntity::ENTITY_RECT, true);
	
	// Revolute Joint	
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 10, 30);
	shape->setPosition(-170, 205);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createRevoluteJoint(shape, ceiling, -640/2, 255);
	scene->applyImpulse(shape, 10, 0);
	
	// Distance Joint	
	shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 10, 30);
	shape->setPosition(-70, 195);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createDistanceJoint(shape, ceiling, false);
	scene->applyImpulse(shape, 200, 0);
	
	SceneLine *line = new SceneLine(shape, ceiling);
	line->setColor(1.0, 0.0, 0.0, 1.0);
	scene->addChild(line);

	// Prismatic Joint	
	shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 10, 30);
	shape->setPosition(130, 45);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createPrismaticJoint(ceiling, shape, Vector2(0,1), 0,0, false, 100, 0, true);

	SceneEntity *lineAnchor = new SceneEntity();
	lineAnchor->setPosition(130,480/2-10);
	line = new SceneLine(shape, lineAnchor);
	line->setColor(0.0, 1.0, 0.0, 1.0);
	scene->addChild(line);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
