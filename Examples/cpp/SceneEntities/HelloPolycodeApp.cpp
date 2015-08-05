#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,true,0,0,90, 0, true);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Scene *scene = new Scene(Scene::SCENE_2D);
	sun = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 0.2,0.2, 30);
	sun->setColor(0.9, 0.8, 0, 1); 
	sun->colorAffectsChildren = false;		
	scene->addChild(sun);
	
	planet = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 0.1,0.1, 30);
	planet->setPosition(0.3,0);
	planet->setColor(0.2, 0.8, 0, 1); 
	planet->colorAffectsChildren = false;
	sun->addChild(planet);

	moon = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 0.05, 0.05, 30);
	moon->setPosition(0.1,0);
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
	moonRoll += elapsed * 6.0;
	planet->setPosition(cosf(planetRoll)*0.3, sinf(planetRoll)*0.3);
	moon->setPosition(cosf(moonRoll)*0.1, sinf(moonRoll)*0.1);
		
    return core->updateAndRender();
}

