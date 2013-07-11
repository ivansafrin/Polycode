#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Screen *screen = new Screen();			
	sun = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 100,100, 30);
	sun->setPosition(640/2, 480/2);
	sun->setColor(0.9, 0.8, 0, 1); 
	sun->colorAffectsChildren = false;		
	screen->addChild(sun);		
	
	planet = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 50,50, 30);
	planet->setPosition(150,0);
	planet->setColor(0.2, 0.8, 0, 1); 
	planet->colorAffectsChildren = false;
	sun->addChild(planet);		

	moon = new ScreenShape(ScreenShape::SHAPE_CIRCLE, 20,20, 30);
	moon->setPosition(50,0);
	moon->setColor(1, 1, 0.6, 1); 
	planet->addChild(moon);		
	
	planetRotation = 0;
	moonRotation = 0;	
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
	planetRotation += elapsed ;
	moonRotation += elapsed * 6;	
	planet->setPosition(cosf(planetRotation)*150, sinf(planetRotation)*150);
	moon->setPosition(cosf(moonRotation)*50, sinf(moonRotation)*50);
		
    return core->updateAndRender();
}

