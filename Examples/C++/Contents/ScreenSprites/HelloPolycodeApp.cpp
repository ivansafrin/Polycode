#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	Screen *screen = new Screen();
	ScreenSprite *sprite = new ScreenSprite("Resources/sprite_sheet.png", 93, 78);
	sprite->setPosition(350,150);
	sprite->setScale(7,7);
	screen->addChild(sprite);
	sprite->addAnimation("ExampleAnimation", "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,29,29,29,29,29,29,29,29,29", 0.03);
	sprite->playAnimation("ExampleAnimation", 0, false);
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
