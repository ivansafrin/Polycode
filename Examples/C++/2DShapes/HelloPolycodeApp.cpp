#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	Screen *screen = new Screen();

	ScreenShape *shape = new ScreenShape(ScreenShape::SHAPE_RECT, 100,100);
	shape->setColor(1.0, 0.0, 0.0, 1.0);
	shape->setPosition(150,240);
	screen->addChild(shape);

	shape = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 100,100);
	shape->setColor(0.0, 1.0, 0.0, 1.0);
	shape->setPosition(260,240);
	screen->addChild(shape);

	shape = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 100,100,3);
	shape->setColor(1.0, 0.0, 1.0, 1.0);
	shape->setPosition(350,240);
	screen->addChild(shape);

	shape = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 100,100,6);
	shape->setColor(0.0, 1.0, 1.0, 1.0);
	shape->setPosition(460,240);
	screen->addChild(shape);
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
