#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	PhysicsScreen *screen = new PhysicsScreen(10, 50);

	ScreenShape *ceiling = new ScreenShape(ScreenShape::SHAPE_RECT, 640, 20);
	ceiling->setColor(0.0, 0.0, 0.0, 1.0);
	ceiling->setPosition(640/2, 10);
	screen->addPhysicsChild(ceiling, PhysicsScreenEntity::ENTITY_RECT, true);
	
	// Revolute Joint	
	ScreenShape *shape = new ScreenShape(ScreenShape::SHAPE_RECT, 10, 30);
	shape->setPosition(150, 20+15);
	screen->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, false);
	screen->createRevoluteJoint(shape, ceiling, 0, -15);
	screen->applyImpulse(shape, 10, 0);
	
	// Distance Joint	
	shape = new ScreenShape(ScreenShape::SHAPE_RECT, 10, 30);
	shape->setPosition(250, 20+25);
	screen->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, false);
	screen->createDistanceJoint(shape, ceiling, false);
	screen->applyImpulse(shape, 200, 0);
	
	ScreenLine *line = new ScreenLine(shape, ceiling);
	line->setColor(1.0, 0.0, 0.0, 1.0);
	screen->addChild(line);

	// Prismatic Joint	
	shape = new ScreenShape(ScreenShape::SHAPE_RECT, 10, 30);
	shape->setPosition(450, 20+25);
	screen->addPhysicsChild(shape, PhysicsScreenEntity::ENTITY_RECT, false);
	screen->createPrismaticJoint(ceiling, shape, Vector2(0,1), 0,0, false, 100, 0, true);

	ScreenEntity *lineAnchor = new ScreenEntity();
	lineAnchor->setPosition(450,10);
	line = new ScreenLine(shape, lineAnchor);
	line->setColor(0.0, 1.0, 0.0, 1.0);
	screen->addChild(line);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
