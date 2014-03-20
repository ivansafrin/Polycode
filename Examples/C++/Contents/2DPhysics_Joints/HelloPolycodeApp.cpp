#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	PhysicsScene2D *scene = new PhysicsScene2D(0.1, 50);

	ScenePrimitive *ceiling = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 2.0, 0.1);
	ceiling->setColor(0.0, 0.0, 0.0, 1.0);
	ceiling->setPosition(0, 0.5);
	scene->addPhysicsChild(ceiling, PhysicsScene2DEntity::ENTITY_RECT, true);
	
	// Revolute Joint	
	ScenePrimitive *shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.03, 0.2);
    shape->setAnchorPoint(0.0, 1.0, 0.0);
	shape->setPosition(-0.3, 0.48);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createRevoluteJoint(shape, ceiling, 0.0, 0.01);
	scene->applyImpulse(shape, 10, 0);
	
	// Distance Joint	
	shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.1, 0.02);
	shape->setPosition(0.0, 0.2);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createDistanceJoint(shape, ceiling, false);
	scene->applyImpulse(shape, 2, 0);
	
	SceneLine *line = new SceneLine(shape, ceiling);
	line->setColor(1.0, 0.0, 0.0, 1.0);
	scene->addChild(line);

	// Prismatic Joint	
	shape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 0.05, 0.1);
	shape->setPosition(0.3, 0.3);
	scene->addPhysicsChild(shape, PhysicsScene2DEntity::ENTITY_RECT, false);
	scene->createPrismaticJoint(ceiling, shape, Vector2(0,1), 0,0, false, -0.3, 0, true);

	SceneEntity *lineAnchor = new SceneEntity();
	lineAnchor->setPosition(0.3,0.5);
	line = new SceneLine(shape, lineAnchor);
	line->setColor(0.0, 1.0, 0.0, 1.0);
	scene->addChild(line);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
