#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,90);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();
	ScreenLabel *label = new ScreenLabel("Hello, Polycode!", 32);
	screen->addChild(label);
}

HelloPolycodeApp::~HelloPolycodeApp() {

}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
