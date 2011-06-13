#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	Screen *screen = new Screen();
	ScreenSprite *sprite = new ScreenSprite("sprite_sheet.png", 93, 78);
	sprite->setPosition(350,150);
	sprite->setScale(7,7);
	screen->addChild(sprite);
	sprite->addAnimation("ExampleAnimation", "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,29,29,29,29,29,29,29,29,29", 0.04);
	sprite->playAnimation("ExampleAnimation", 0, false);
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
