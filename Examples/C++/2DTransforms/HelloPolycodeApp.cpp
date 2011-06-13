#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();			
	for(Number i=0; i < 10; i++) {
		ScreenImage *image = new ScreenImage("polycode_logo.png");
		screen->addChild(image);	
		image->setPosition(160+(42*i), 230);
		image->setPositionMode(ScreenEntity::POSITION_CENTER);
		image->setRotation(45*i);
		image->setScale(1.0-(0.1*i),1.0-(0.1*i));
	}
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
