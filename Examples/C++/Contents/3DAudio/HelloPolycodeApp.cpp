#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	Scene *scene = new Scene();
	
	sourceEntity = new SceneEntity();
	SceneSound *testSound = new SceneSound("Resources/test.wav", 20, 50);
	testSound->getSound()->Play(true);
	sourceEntity->addChild(testSound);
	ScenePrimitive *soundShape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
	soundShape->setMaterialByName("Default");
	sourceEntity->addChild(soundShape);	
	scene->addEntity(sourceEntity);
	
	SceneLight *light = new SceneLight(SceneLight::AREA_LIGHT, scene, 1000);
	scene->addLight(light);

	SceneSoundListener *soundListener = new SceneSoundListener();
	scene->addEntity(soundListener);

	positionValue = 0;
	
}

HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	positionValue += core->getElapsed();
	
	sourceEntity->setPosition((sin(positionValue) * 20), 0, cos(positionValue) * 50); 
	sourceEntity->Roll(core->getElapsed() * 120);
	sourceEntity->Pitch(core->getElapsed()* 120);	
		
    return core->updateAndRender();
}
