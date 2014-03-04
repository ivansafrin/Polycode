#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene(Scene::SCENE_2D);			
	sun = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 100,100, 30);
	sun->setColor(0.9, 0.8, 0, 1); 
	sun->colorAffectsChildren = false;		
	scene->addChild(sun);
	
	planet = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 50,50, 30);
	planet->setPosition(150,0);
	planet->setColor(0.2, 0.8, 0, 1); 
	planet->colorAffectsChildren = false;
	sun->addChild(planet);

	moon = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 20,20, 30);
	moon->setPosition(50,0);
	moon->setColor(1, 1, 0.6, 1);
	planet->addChild(moon);
	
	planetRoll = 0;
	moonRoll = 0;	
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	Number elapsed = core->getElapsed();
	planetRoll += elapsed ;
	moonRoll += elapsed * 6;	
	planet->setPosition(cosf(planetRoll)*150, sinf(planetRoll)*150);
	moon->setPosition(cosf(moonRoll)*50, sinf(moonRoll)*50);
		
    return core->updateAndRender();
}

