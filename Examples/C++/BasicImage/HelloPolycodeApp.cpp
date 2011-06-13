#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();			
	ScreenImage *image = new ScreenImage("polycode_logo.png");
	screen->addChild(image);	
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
