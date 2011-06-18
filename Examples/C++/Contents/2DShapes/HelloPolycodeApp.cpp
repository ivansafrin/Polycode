#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

#ifdef __APPLE__
	core = new CocoaCore(view, 640,480,false,false,0,0,90);	  
#else
	core = new SDLCore(view, 640,480,false,false,0,0,90);	  
#endif

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
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
