#include "HelloPolycodeApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
    	core = new SDLCore(view, 640,480,false,0,90);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);

	Scene *scene = new Scene();
	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 5,5);
	ground->setMaterialByName("GroundMaterial");
	scene->addEntity(ground);

	ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1,1,1);
	box->setMaterialByName("CubeMaterial");
	box->setPosition(0.0, 0.5, 0.0);
	scene->addEntity(box);
	
	SceneLight *light = new SceneLight(SceneLight::AREA_LIGHT, scene, 3);
	light->setPosition(1,2,1);
	scene->addLight(light);

	scene->getDefaultCamera()->setPosition(7,7,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
}

bool HelloPolycodeApp::Update() {
    return core->Update();
}
