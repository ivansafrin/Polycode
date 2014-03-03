#include "HelloPolycodeApp.h"
	
HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) {

	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);	  
	
	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);	

	Scene *scene = new Scene(Scene::SCENE_2D_TOPLEFT);
	
	sourceEntity = new SceneEntity();
	SceneSound *testSound = new SceneSound("Resources/test.wav", 200, 600);
	testSound->getSound()->Play(true);
	sourceEntity->addChild(testSound);
	ScenePrimitive *soundShape = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 20,20,10);
	sourceEntity->addChild(soundShape);	
	scene->addChild(sourceEntity);
	
	listenerEntity = new ScreenEntity();
	SceneSoundListener *soundListener = new SceneSoundListener();
	listenerEntity->addChild(soundListener);
	soundShape = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 20,20,10);
	soundShape->setColor(0.0, 1.0, 0.0, 1.0);
	listenerEntity->addChild(soundShape);	
	scene->addChild(listenerEntity);

	listenerPositionValue = 0;
	positionValue = 0;	
}

HelloPolycodeApp::~HelloPolycodeApp() {
    
}

bool HelloPolycodeApp::Update() {
	positionValue += core->getElapsed();
	listenerPositionValue += core->getElapsed() * 0.3;	
	
	sourceEntity->setPosition(300 + (sin(positionValue) * 300), 250 + cos(positionValue) * 100); 
	listenerEntity->setPosition(300 + (sin(listenerPositionValue) * 300), 250); 
		
    return core->updateAndRender();
}
