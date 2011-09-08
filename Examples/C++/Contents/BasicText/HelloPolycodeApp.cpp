#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

#ifdef __APPLE__
	core = new CocoaCore(view, 640,480,false,0,90);	  
#else
	core = new SDLCore(view, 640,480,false,0,90);	  
#endif

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();
	ScreenLabel *label = new ScreenLabel("Hello, Polycode!", 32);
	screen->addChild(label);
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
